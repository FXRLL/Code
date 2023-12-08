import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

class PixelPaintApp extends JFrame {
    private Color currentColor;

    public PixelPaintApp() {
        setTitle("像素绘图应用");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        currentColor = Color.BLACK;

        // 添加菜单栏
        JMenuBar menuBar = new JMenuBar();

        // 文件菜单
        JMenu fileMenu = new JMenu("文件");
        fileMenu.setMnemonic(KeyEvent.VK_F);

        // 保存
        JMenuItem saveMenuItem = new JMenuItem("保存");
        saveMenuItem.setMnemonic(KeyEvent.VK_S);
        saveMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                saveDrawing();
            }
        });

        // 读取
        JMenuItem loadMenuItem = new JMenuItem("加载");
        loadMenuItem.setMnemonic(KeyEvent.VK_L);
        loadMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                loadDrawing();
            }
        });

        // 导出成图片
        JMenuItem exportImageMenuItem = new JMenuItem("导出为图片");
        exportImageMenuItem.setMnemonic(KeyEvent.VK_E);
        exportImageMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                exportAsImage();
            }
        });

        // 清空画布
        JMenuItem clearCanvasMenuItem = new JMenuItem("清空画布");
        clearCanvasMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clearCanvas();
            }
        });

        fileMenu.add(saveMenuItem);
        fileMenu.add(loadMenuItem);
        fileMenu.add(exportImageMenuItem);
        fileMenu.add(clearCanvasMenuItem);

        // 颜色菜单
        JMenu colorMenu = new JMenu("颜色");

        JMenuItem blackMenuItem = createColorMenuItem("黑色", Color.BLACK);
        JMenuItem redMenuItem = createColorMenuItem("红色", Color.RED);
        JMenuItem yellowMenuItem = createColorMenuItem("黄色", Color.YELLOW);
        JMenuItem blueMenuItem = createColorMenuItem("蓝色", Color.BLUE);

        JMenuItem chooseColorMenuItem = new JMenuItem("选择颜色");
        chooseColorMenuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                chooseColor();
            }
        });


        colorMenu.add(blackMenuItem);
        colorMenu.add(redMenuItem);
        colorMenu.add(yellowMenuItem);
        colorMenu.add(blueMenuItem);
        colorMenu.addSeparator();
        colorMenu.add(chooseColorMenuItem);

        menuBar.add(fileMenu);
        menuBar.add(colorMenu);
        setJMenuBar(menuBar);

        // 添加鼠标事件监听器
        addMouseListener(new PaintMouseListener());
        addMouseMotionListener(new PaintMouseListener());

        // 设置布局为流式布局
        setLayout(new FlowLayout());
    }

    private JMenuItem createColorMenuItem(String label, Color color) {
        JMenuItem menuItem = new JMenuItem(label);
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                currentColor = color;
            }
        });
        return menuItem;
    }

    private void saveDrawing() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(fileChooser.getSelectedFile()))) {
                // 保存绘图信息到文件
                List<DrawInfo> drawInfoList = getDrawInfoList();
                oos.writeObject(drawInfoList);
                showCompletionDialog("保存完成");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }


    private void loadDrawing() {
        JFileChooser fileChooser = new JFileChooser();
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fileChooser.getSelectedFile()))) {
                // 从文件中读取绘图信息
                List<DrawInfo> drawInfoList = (List<DrawInfo>) ois.readObject();
                drawFromInfoList(drawInfoList);
                showCompletionDialog("加载完成");
            } catch (IOException | ClassNotFoundException ex) {
                ex.printStackTrace();
            }
        }
    }

    private void exportAsImage() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("导出为图片");
        fileChooser.setFileFilter(new FileNameExtensionFilter("PNG 图片", "png"));

        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            try {
                BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
                Graphics2D g = image.createGraphics();

                // 使用双缓冲技术，先绘制到内存中的图像，再一次性绘制到屏幕上
                paint(g);

                File selectedFile = fileChooser.getSelectedFile();
                String filePath = selectedFile.getAbsolutePath();
                if (!filePath.toLowerCase().endsWith(".png")) {
                    selectedFile = new File(filePath + ".png");
                }

                ImageIO.write(image, "png", selectedFile);
                showCompletionDialog("导出完成");
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

    private void showCompletionDialog(String message) {
        // 创建一个面板并设置为网格布局
        JPanel panel = new JPanel(new GridLayout(2, 1));

        // 添加组件到面板
        JLabel messageLabel = new JLabel(message);
        messageLabel.setHorizontalAlignment(JLabel.CENTER);
        panel.add(messageLabel);

        // 添加一个空白面板，以使文本垂直居中
        panel.add(new JPanel());

        // 显示网格布局的JOptionPane对话框
        JOptionPane.showMessageDialog(this, panel, "操作完成", JOptionPane.INFORMATION_MESSAGE);
    }


    private void clearCanvas() {
        getContentPane().removeAll();
        repaint();
        showCompletionDialog("清空画布完成");
    }

    private void chooseColor() {
        Color selectedColor = JColorChooser.showDialog(this, "选择颜色", currentColor);
        if (selectedColor != null) {
            currentColor = selectedColor;
        }
    }

    private static class DrawInfo implements Serializable {
        private int x;
        private int y;
        private int width;
        private int height;
        private Color color;

        public DrawInfo(int x, int y, int width, int height, Color color) {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
            this.color = color;
        }
    }

    private void drawFromInfoList(List<DrawInfo> drawInfoList) {
        getContentPane().removeAll();
        for (DrawInfo drawInfo : drawInfoList) {
            drawPixel(drawInfo);
        }
        repaint();
    }

    private List<DrawInfo> getDrawInfoList() {
        List<DrawInfo> drawInfoList = new ArrayList<>();
        Component[] components = getContentPane().getComponents();
        for (Component component : components) {
            if (component instanceof JPanel) {
                JPanel panel = (JPanel) component;
                drawInfoList.add(new DrawInfo(panel.getX(), panel.getY(),
                        panel.getWidth(), panel.getHeight(), panel.getBackground()));
            }
        }
        return drawInfoList;
    }

    private void drawPixel(DrawInfo drawInfo) {
        int x = drawInfo.x;
        int y = drawInfo.y;
        int width = drawInfo.width;
        int height = drawInfo.height;
        Color color = drawInfo.color;

        JPanel pixel = new JPanel();
        pixel.setBounds(x, y, width, height);
        pixel.setBackground(color);
        getContentPane().add(pixel);
    }

    private class PaintMouseListener extends java.awt.event.MouseAdapter {
        @Override
        public void mousePressed(java.awt.event.MouseEvent e) {
            drawPixel(e);
        }

        @Override
        public void mouseDragged(java.awt.event.MouseEvent e) {
            drawPixel(e);
        }

        private void drawPixel(java.awt.event.MouseEvent e) {
            int pixelSize = 5;  // 定义像素的大小
            int x = e.getX() - pixelSize / 2;
            int y = e.getY() - pixelSize / 2;

            JPanel pixel = new JPanel();
            pixel.setBounds(x, y, pixelSize, pixelSize);
            pixel.setBackground(currentColor);
            getContentPane().add(pixel);
            repaint();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new PixelPaintApp().setVisible(true));
    }
}