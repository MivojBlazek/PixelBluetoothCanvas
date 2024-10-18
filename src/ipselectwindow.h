#ifndef IPSELECTWINDOW_H
#define IPSELECTWINDOW_H

#include <QWidget>

namespace Ui {
class IPSelectWindow;
}

class IPSelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IPSelectWindow(QWidget *parent = nullptr);
    ~IPSelectWindow();

private:
    Ui::IPSelectWindow *ui;
    void onConnectButtonClicked();
};

#endif // IPSELECTWINDOW_H
