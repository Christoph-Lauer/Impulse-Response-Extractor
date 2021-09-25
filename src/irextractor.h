#ifndef IREXTRACTOR_H
#define IREXTRACTOR_H

#include <QMainWindow>
#include <QtMultimedia>

QT_BEGIN_NAMESPACE
namespace Ui { class IRExtractor; }
QT_END_NAMESPACE

class IRExtractor : public QMainWindow
{
    Q_OBJECT

public:
    IRExtractor(QWidget *parent = nullptr);
    ~IRExtractor();

private slots:
    void on_sweepButton_clicked();

private:
    Ui::IRExtractor *ui;
};


#endif // IREXTRACTOR_H
