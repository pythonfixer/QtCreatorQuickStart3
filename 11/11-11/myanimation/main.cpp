#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Animated Button");
    button.show();

    QPropertyAnimation *animation1 = new QPropertyAnimation(&button, "geometry");
    animation1->setDuration(2000);
    animation1->setStartValue(QRect(250, 0, 120, 30));
    animation1->setEndValue(QRect(250, 300, 120, 30));
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    QPropertyAnimation *animation2 = new QPropertyAnimation(&button, "geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(QRect(250, 300, 120, 30));
    animation2->setEndValue(QRect(250, 300, 200, 60));

    QSequentialAnimationGroup group;
    group.addAnimation(animation1);
    group.addAnimation(animation2);
    group.start();

    return app.exec();
}
