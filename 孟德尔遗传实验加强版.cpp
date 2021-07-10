#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
#include <map>
#include<fstream>
#include <random>
#include<conio.h>
#include<graphics.h>
IMAGE img[10];
int text_length; // 用户输入字符串的长度
void setstr(int x, int y, const wchar_t s[])
{
    LOGFONT i;
    gettextstyle(&i); // 获取当前字体设置
    i.lfHeight = 44; // 设置字体高度为 44
    _tcscpy_s(i.lfFaceName, _T("黑体")); // 设置字体为黑体
    i.lfQuality = ANTIALIASED_QUALITY; // 设置输出效果抗锯齿
    settextstyle(&i); // 设置字体样式
    outtextxy(x, y, s);
}
//指定位置输出字符串
class settextbox
{
public:
    void setting(int a, int b, int c, int d, wchar_t* e) { width_a = a; width_b = c; high_a = b; high_b = d; begin_text = e; }
    void drawtextbox();//文本框加载
    void AddDeleteCharacter();//文本框输入
private:
    int width_a;
    int high_a;
    int width_b;
    int high_b;
    wchar_t* begin_text;//文本框标题
    wchar_t input_text[45] = {' '}; // 用户输入的字符串
    wchar_t c;
};
void settextbox::drawtextbox()
{
    LOGFONT f;
    setfillcolor(RGB(255, 255, 255)); // 设置输入框颜色
    solidrectangle(width_a, high_a, width_b, high_b);
    gettextstyle(&f); // 获取当前字体设置
    f.lfHeight = 44; // 设置字体高度为 44
    _tcscpy_s(f.lfFaceName, _T("黑体")); // 设置字体为黑体
    f.lfQuality = ANTIALIASED_QUALITY; // 设置输出效果抗锯齿
    settextstyle(&f); // 设置字体样式
    setbkmode(TRANSPARENT);
    settextcolor(RGB(0,0, 0)); // 设置字体颜色
    outtextxy(width_a + (width_b - width_a) / 2 - textwidth(begin_text) / 2, high_a - 46, begin_text);
}
void settextbox::AddDeleteCharacter()
{
    if (_kbhit())
    {
        c = _getwch();
        if (c != 8) // 判断输入是否为BACK键
        {
            if (c == 27) // 判断输入是否为ESC键
            {
                EndBatchDraw(); // 结束绘图
                closegraph(); // 关闭绘图窗口
                exit(0); // 退出程序
            }
            if (text_length < 44)
            {
                input_text[text_length] = c;
                input_text[text_length + 1] = '\0';
                text_length++;
            }
        }
        else
        {
            if (text_length > 0)
            {
                text_length--;
                input_text[text_length] = '\0';
            }
        }
    }
    setstr(width_a + 30, high_a + ((high_b - high_a) / 2 - 15), input_text);
}// 添加与删除字符
struct mathers
{
    int i = 1;//相对形状数
    std::string genotype[10] = { "0" };
}mather;
//母本结构
struct fathers
{
    std::string genotype[10] = { "0" };
}father;
//父本结构
void loadIMAGE()
{
    loadimage(&img[0], _T("C:\\Users\\Administrator\\Desktop\\孟德尔遗传实验图片\\begin_ui.png"));//开始
    loadimage(&img[1], _T("C:\\Users\\Administrator\\Desktop\\孟德尔遗传实验图片\\setting_ui.png"));//设置
}
//图片加载
void get_RT_number()
{
    wchar_t ch[100]=L"请输入相对性状的对数:";
    settextbox sb;
    sb.setting(950, 350, 1350, 400, ch);
    BeginBatchDraw();
    while(true)
    {
        cleardevice();
        putimage(0, 0, &img[0]);
        putimage(1550, 0, &img[1]);
        sb.drawtextbox();
        sb.AddDeleteCharacter();
        setstr(1380, 350, L"对");
        FlushBatchDraw();
        Sleep(10);
    }
    EndBatchDraw();
}
int main()
{
    initgraph(1600, 900);
    loadIMAGE();
    get_RT_number();
    getchar();
    return 0;
}