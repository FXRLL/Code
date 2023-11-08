#include <iostream>
#include <graphics.h> 
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
//�������ʱ�����������ڣ���windows 11һ�θ��µ��µ�bug���������������ã����ն˴ӡ���Windows��������Ϊ��Windows����̨������
//��������ʵ�����£�
//c�����棬v�����أ��浵��save.txt��ʽ�����ͬһĿ¼
//��ͣʱ��n���ݱ�һ����m������һ��(�������һ��)��������һ��lastevolve.txt�ļ�
//p���������ϸ��
const int ROWS = 75; // ��Ϸ���������
const int COLS = 100; // ��Ϸ���������
const int CELL_SIZE = 10; // ϸ���Ĵ�С
class Automaton 
{
private:
    class Cell
    {
    public:
        bool state; // ��������״̬
        Cell()
        {
            state = false;
        }
        // ͳ��ĳ��ϸ����Χ�Ĵ��ϸ������
        int GetNeighborCount(Cell** board, int rows, int cols, int row, int col)
        {
            int count = 0;
            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = col - 1; j <= col + 1; j++)
                {
                    // ����߽����
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
    Cell** board; // ��Ϸ����
    bool is_paused; // ��Ϸ�Ƿ�����ͣ״̬
    bool recentStates[3][ROWS][COLS];
public:
    Automaton()
    {
        is_paused = false;
        // ������Ϸ����
        board = new Cell * [ROWS];
        for (int i = 0; i < ROWS; i++)
        {
            board[i] = new Cell[COLS];
        }
    }
    // �����������ͷ��ڴ�
    ~Automaton()
    {
        // ɾ����Ϸ����
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
                int r = rand() % 2; // ������� 0 �� 1
                board[i][j].state = (r == 1);
            }
        }
    }
    // ������Ϸ����
    void run()
    {
        if (!is_paused) 
        {
            Cell new_board[ROWS][COLS]; // �µ���Ϸ����
            for (int i = 0; i < ROWS; i++) 
            {
                for (int j = 0; j < COLS; j++) 
                {
                    int count = board[i][j].GetNeighborCount(board, ROWS, COLS, i, j);
                    if (board[i][j].state) 
                    {
                        // ���ϸ���ĸ��¹���
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
                        // ����ϸ���ĸ��¹���
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
            // ���µ���Ϸ���渴�Ƶ�ԭ������Ϸ������
            for (int i = 0; i < ROWS; i++) 
            {
                for (int j = 0; j < COLS; j++) 
                {
                    board[i][j].state = new_board[i][j].state;
                }
            }
        }
    }
    // ������Ϸ����
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
    // ��ͣ�������Ϸ
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
        // ����ÿ��ϸ����״̬
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
        // ��ȡÿ��ϸ����״̬
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
        // ����һ������״̬�洢�ڵ���ά������
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                recentStates[2][i][j] = recentStates[1][i][j];
            }
        }
        // ����һ������״̬�洢�ڵڶ�ά������
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                recentStates[1][i][j] = recentStates[0][i][j];
            }
        }
        // ����ǰ����״̬�洢�ڵ�һά������
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
                SetCell(row, col, true); // ����ϸ��״̬Ϊ���
            }
            else if (m.uMsg == WM_RBUTTONUP || (m.uMsg == WM_MOUSEMOVE && m.mkRButton)) 
            {
                int row = m.y / CELL_SIZE;
                int col = m.x / CELL_SIZE;
                SetCell(row, col, false); // ����ϸ��״̬Ϊ����
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
    initgraph(COLS * CELL_SIZE, ROWS * CELL_SIZE); // ��ʼ��ͼ�δ���
    Automaton board;
    board.Init(); // ��ʼ����Ϸ����
    PlaySound(TEXT("background_music.wav"), NULL, SND_ASYNC | SND_LOOP);
    bool is_paused = false;
    while (true) 
    {
        board.Display(); // ������Ϸ����
        board.handleMouseActions();//���������
        //�����̲���
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
            board.run(); // ������Ϸ����
            board.storeRecentStates();//�洢״̬
            if (board.isRecentStatesEqual(0, 1))//���״̬
                board.Evolutionstops();//��ʾ��Ϣ
            else if (board.isRecentStatesEqual(0, 2))//���״̬
                board.Evolutioncycle();//��ʾ��Ϣ
            Sleep(25);//��ͣ25ms
        }
    }
    closegraph(); // �ر�ͼ�δ���
    PlaySound(NULL, NULL, 0);
    return 0;
}