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

    std::vector<float> time;
    std::vector<float> amounts;

    time.push_back(0.0);
    time.push_back(1.0);
    time.push_back(2.0);

    amounts.push_back(-100.0);
    amounts.push_back(  10.0);
    amounts.push_back( 110.0);

    float res = 0.05;
    float pvv = pv.pv_discrete_cflow(time, amounts, res);
    float irr = pv.irr_discrete_cflow(time,amounts);
    bool  found = pv.unique_discrete_irr(time,amounts);

    std::cout << "Present value, 5 persent discretely compounded interest = " << pvv << std::endl;
    std::cout << "Internal rate of return, discrete compounding = " << irr << std::endl;
    if (found)
        std::cout << "Real solution found" << std::endl;
    else
        std::cout << "No meaningful solution found" << std::endl;

    return a.exec();
}
