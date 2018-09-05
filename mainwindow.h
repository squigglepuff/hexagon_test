#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

protected:
    void paintEvent(QPaintEvent *apEvent);

private:
    bool DrawHexagon(QPainter *pPainter = nullptr, const QPointF aCenter = QPointF(0.0f, 0.0f), const float aSize = 512.0f);
};

#endif // MAINWINDOW_H
