#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

// Forward declarations - NO UI namespace!
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseInputFile();
    void browseOutputFile();
    void processFiles();
    void clearLog();

private:
    void setupUI();
    void setupConnections();
    void logMessage(const QString &message);

    // UI elements
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    QLabel *titleLabel;
    QLabel *inputLabel;
    QLineEdit *inputFileLineEdit;
    QPushButton *inputBrowseButton;

    QLabel *outputLabel;
    QLineEdit *outputFileLineEdit;
    QPushButton *outputBrowseButton;

    QPushButton *processButton;
    QPushButton *clearButton;

    QLabel *logLabel;
    QTextEdit *logTextEdit;

    // File paths storage
    QString m_inputFilePath;
    QString m_outputFilePath;
};

#endif // MAINWINDOW_H
