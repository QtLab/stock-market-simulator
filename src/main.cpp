#include <QApplication>
#include "main_window.hpp"
#include "present_value.hpp"

#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    finance::PresentValue<float> pv;

    std::vector<float> time(1000);
    std::vector<float> amounts(1000, 1);

    for (unsigned i = 0; i < time.size(); i++) time[i] = i;

    float res = 0.1;
    std::cout << pv.pv_discrete_cflow(time, amounts, res) << std::endl;

    return a.exec();
}
