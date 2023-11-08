#include <iostream>
#include <graphics.h> 
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
//如果运行时出现两个窗口，是windows 11一次更新导致的bug，搜索开发者设置，将终端从“让Windows决定”改为“Windows控制台主机”
//交互功能实现如下：
//c键保存，v键加载，存档以save.txt形式存放在同一目录
//暂停时，n键演变一代，m键返回一代(返回最多一代)，会生成一个lastevolve.txt文件
//p键清除所有细胞
const int ROWS = 75; // 游戏板面的行数
const int COLS = 100; // 游戏板面的列数
const int CELL_SIZE = 10; // 细胞的大小
class Automaton 
{
private:
    class Cell
    {
    public:
        bool state; // 存活或死亡状态
        Cell()
        {
            state = false;
        }
        // 统计某个细胞周围的存活细胞数量
        int GetNeighborCount(Cell** board, int rows, int cols, int row, int col)
        {
            int count = 0;
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    // 处理边界情况
                    int r = (i + rows) % rows;
                    int c = (j + cols) % cols;

                    if (!(i == row && j == col) && board[r][c].state)
                    {
                        count++;
                    }
                }
            }
            return count;
        }
        void Display(int x, int y)
        {
            if (state)
            {
                setfillcolor(BLACK);
            }
            else
            {
                setfillcolor(WHITE);
            }
            fillrectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);
        }
    };
    Cell** board; // 游戏板面
    bool is_paused; // 游戏是否处于暂停状态
    bool recentStates[3][ROWS][COLS];
public:
    Automaton()
    {
        is_paused = false;
        // 创建游戏板面
        board = new Cell * [ROWS];
        for (int i = 0; i < ROWS; i++)
        {
            board[i] = new Cell[COLS];
        }
    }
    // 析构函数，释放内存
    ~Automaton()
    {
        // 删除游戏板面
        for (int i = 0; i < ROWS; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }
    void Init()
    {
        srand(time(NULL));
        for (int i = 0; i < ROWS; i++)  
        {
            for (int j = 0; j < COLS; j++) 
            {
                int r = rand() % 2; // 随机生成 0 或 1
                board[i][j].state = (r == 1);
            }
        }
    }
    // 更新游戏板面
    void run()
    {
        if (!is_paused) 
        {
            Cell new_board[ROWS][COLS]; // 新的游戏板面
            for (int i = 0; i < ROWS; i++) 
            {
                for (int j = 0; j < COLS; j++) 
                {
                    int count = board[i][j].GetNeighborCount(board, ROWS, COLS, i, j);
                    if (board[i][j].state) 
                    {
                        // 存活细胞的更新规则
                        if (count < 2 || count > 3) 
                        {
                            new_board[i][j].state = false;
                        }
                        else 
                        {
                            new_board[i][j].state = true;
                        }
                    }
                    else 
                    {
                        // 死亡细胞的更新规则
                        if (count == 3) 
                        {
                            new_board[i][j].state = true;
                        }
                        else 
                        {
                            new_board[i][j].state = false;
                        }
                    }
                }
            }
            // 将新的游戏板面复制到原来的游戏板面中
            for (int i = 0; i < ROWS; i++) 
            {
                for (int j = 0; j < COLS; j++) 
                {
                    board[i][j].state = new_board[i][j].state;
                }
            }
        }
    }
    // 绘制游戏板面
    void Display()
    {
        BeginBatchDraw();
        setbkcolor(WHITE);
        cleardevice();

        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                int x = j * CELL_SIZE;
                int y = i * CELL_SIZE;
                board[i][j].Display(x, y);
            }
        }

        EndBatchDraw();
    }
    // 暂停或继续游戏
    void TogglePause() 
    {
        is_paused = !is_paused;
    }
    void SetCell(int row, int col, bool state) 
    {
        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) 
        {
            board[row][col].state = state;
        }
    }
    std::vector<std::vector<bool>> getAllCellStates() const 
    {
        std::vector<std::vector<bool>> states(ROWS, std::vector<bool>(COLS));
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                states[i][j] = board[i][j].state;
            }
        }
        return states;
    }
    void saveToFile(const std::string& filename) 
    {
        std::ofstream fout(filename);
        // 保存每个细胞的状态
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                fout << board[i][j].state << " ";
            }
            fout << std::endl;
        }
        fout.close();
    }
    void loadFromFile(const std::string& filename) 
    {
        std::ifstream fin(filename);
        // 读取每个细胞的状态
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                fin >> board[i][j].state;
            }
        }
        fin.close();
    }
    void clearBoard() 
    {
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                board[i][j].state = false;
            }
        }
    }
    void storeRecentStates() 
    {
        // 将上一次棋盘状态存储在第三维数组中
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                recentStates[2][i][j] = recentStates[1][i][j];
            }
        }
        // 将上一次棋盘状态存储在第二维数组中
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                recentStates[1][i][j] = recentStates[0][i][j];
            }
        }
        // 将当前棋盘状态存储在第一维数组中
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                recentStates[0][i][j] = board[i][j].state;
            }
        }
    }
    bool isRecentStatesEqual(int arr1,int arr2)
    {
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                if (recentStates[arr1][i][j] != recentStates[arr2][i][j]) 
                {
                    return false;
                }
            }
        }
        return true;
    }
    void handleMouseActions() 
    {
        while (MouseHit()) 
        {
            MOUSEMSG m = GetMouseMsg();
            if (m.uMsg == WM_LBUTTONDOWN || (m.uMsg == WM_MOUSEMOVE && m.mkLButton)) 
            {
                int row = m.y / CELL_SIZE;
                int col = m.x / CELL_SIZE;
                SetCell(row, col, true); // 设置细胞状态为存活
            }
            else if (m.uMsg == WM_RBUTTONUP || (m.uMsg == WM_MOUSEMOVE && m.mkRButton)) 
            {
                int row = m.y / CELL_SIZE;
                int col = m.x / CELL_SIZE;
                SetCell(row, col, false); // 设置细胞状态为死亡
            }
        }
    }
    void Evolutionstops()
    {
        wchar_t s[] = L"Evolution stops";
        settextstyle(ROWS / 2, 0, _T("Consolas"));
        settextcolor(RGB(0, 0, 0));
        outtextxy(COLS * CELL_SIZE / 2 - 150, ROWS * CELL_SIZE / 2, s);
    }
    void Evolutioncycle()
    {
        wchar_t s[] = L"Evolution cycle";
        settextstyle(ROWS / 2, 0, _T("Consolas"));
        settextcolor(RGB(0, 0, 0));
        outtextxy(COLS * CELL_SIZE / 2 - 150, ROWS * CELL_SIZE / 2, s);
    }
};
int main()
{
    initgraph(COLS * CELL_SIZE, ROWS * CELL_SIZE); // 初始化图形窗口
    Automaton board;
    board.Init(); // 初始化游戏板面
    PlaySound(TEXT("background_music.wav"), NULL, SND_ASYNC | SND_LOOP);
    bool is_paused = false;
    while (true) 
    {
        board.Display(); // 绘制游戏板面
        board.handleMouseActions();//检测鼠标操作
        //检测键盘操作
        {
            if (_kbhit())
            {
                char boardhit = _getch();
                switch (boardhit)
                {
                case' ':
                {
                    is_paused = !is_paused;
                    break;
                }
                case'c':
                {
                    vector<vector<bool>> cellStates = board.getAllCellStates();
                    board.saveToFile("save.txt");
                    break;
                }
                case'v':
                {
                    board.loadFromFile("save.txt");
                    break;
                }
                case'p':
                {
                    board.clearBoard();
                    break;
                }
                case'n':
                {
                    board.saveToFile("lastevolve.txt");
                    board.run();
                    break;
                }
                case'm':
                {
                    board.loadFromFile("lastevolve.txt");
                    break;
                }
                }
            }
        }
        if (!is_paused) 
        {
            board.run(); // 更新游戏板面
            board.storeRecentStates();//存储状态
            if (board.isRecentStatesEqual(0, 1))//检测状态
                board.Evolutionstops();//显示消息
            else if (board.isRecentStatesEqual(0, 2))//检测状态
                board.Evolutioncycle();//显示消息
            Sleep(25);//暂停25ms
        }
    }
    closegraph(); // 关闭图形窗口
    PlaySound(NULL, NULL, 0);
    return 0;
}