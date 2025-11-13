#include "mainwindow.h"
#include "ptom.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDateTime>
#include <QScrollBar>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , mainLayout(nullptr)
{
    setupUI();
    setupConnections();

    logMessage("The Denigifier started successfully.");
    logMessage("Ready to process files.");
}

MainWindow::~MainWindow()
{
    // Qt automatically deletes child widgets
}

void MainWindow::setupUI()
{
    // Create central widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create main layout
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // Title
    titleLabel = new QLabel("The Denigifier - Deobfuscation Tool");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    // Input file section
    inputLabel = new QLabel("Input File:");
    inputLabel->setStyleSheet("font-weight: bold;");

    inputFileLineEdit = new QLineEdit();
    inputFileLineEdit->setReadOnly(true);
    inputFileLineEdit->setPlaceholderText("Select input file...");
    inputFileLineEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #bdc3c7; border-radius: 3px; }");

    inputBrowseButton = new QPushButton("Browse...");
    inputBrowseButton->setStyleSheet("QPushButton { padding: 5px 15px; background-color: #3498db; color: white; border: none; border-radius: 3px; }"
                                     "QPushButton:hover { background-color: #2980b9; }");

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputFileLineEdit, 1);
    inputLayout->addWidget(inputBrowseButton);

    // Output file section
    outputLabel = new QLabel("Output File:");
    outputLabel->setStyleSheet("font-weight: bold;");

    outputFileLineEdit = new QLineEdit();
    outputFileLineEdit->setReadOnly(true);
    outputFileLineEdit->setPlaceholderText("Select output file...");
    outputFileLineEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #bdc3c7; border-radius: 3px; }");

    outputBrowseButton = new QPushButton("Browse...");
    outputBrowseButton->setStyleSheet("QPushButton { padding: 5px 15px; background-color: #3498db; color: white; border: none; border-radius: 3px; }"
                                      "QPushButton:hover { background-color: #2980b9; }");

    QHBoxLayout *outputLayout = new QHBoxLayout();
    outputLayout->addWidget(outputLabel);
    outputLayout->addWidget(outputFileLineEdit, 1);
    outputLayout->addWidget(outputBrowseButton);

    // Process buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    processButton = new QPushButton("Process Files");
    processButton->setStyleSheet("QPushButton { padding: 10px 20px; background-color: #27ae60; color: white; font-weight: bold; border: none; border-radius: 3px; font-size: 14px; }"
                                 "QPushButton:hover { background-color: #219a52; }"
                                 "QPushButton:disabled { background-color: #95a5a6; }");
    processButton->setEnabled(false);

    clearButton = new QPushButton("Clear Log");
    clearButton->setStyleSheet("QPushButton { padding: 10px 20px; background-color: #e74c3c; color: white; border: none; border-radius: 3px; }"
                               "QPushButton:hover { background-color: #c0392b; }");

    buttonLayout->addWidget(processButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addStretch();

    // Log section
    logLabel = new QLabel("Activity Log:");
    logLabel->setStyleSheet("font-weight: bold;");

    logTextEdit = new QTextEdit();
    logTextEdit->setReadOnly(true);
    logTextEdit->setMaximumHeight(150);
    logTextEdit->setStyleSheet("QTextEdit { background-color: #f8f9fa; border: 1px solid #bdc3c7; border-radius: 3px; font-family: monospace; }");

    // Assemble main layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(outputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(logLabel);
    mainLayout->addWidget(logTextEdit);

    // Set window properties
    setWindowTitle("The Denigifier v0.1");
    setMinimumSize(700, 500);
    resize(700, 500);
}

void MainWindow::setupConnections()
{
    connect(inputBrowseButton, &QPushButton::clicked, this, &MainWindow::browseInputFile);
    connect(outputBrowseButton, &QPushButton::clicked, this, &MainWindow::browseOutputFile);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::processFiles);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearLog);
}

void MainWindow::browseInputFile()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Input File",
        QDir::homePath(),
        "All Files (*.*);;Text Files (*.txt);;C/C++ Files (*.c *.cpp *.h);;Executable Files (*.exe *.bin)"
        );

    if (!filePath.isEmpty()) {
        m_inputFilePath = filePath;
        inputFileLineEdit->setText(filePath);

        logMessage("Input file selected: " + filePath);

        // Auto-generate output filename
        QFileInfo inputInfo(filePath);
        QString outputPath = inputInfo.path() + "/" + inputInfo.completeBaseName() + "_deobfuscated." + inputInfo.suffix();
        m_outputFilePath = outputPath;
        outputFileLineEdit->setText(outputPath);

        logMessage("Output file auto-generated: " + outputPath);

        // Enable process button
        processButton->setEnabled(true);
    }
}

void MainWindow::browseOutputFile()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Select Output File",
        m_outputFilePath.isEmpty() ? QDir::homePath() : m_outputFilePath,
        "All Files (*.*);;Text Files (*.txt);;C/C++ Files (*.c *.cpp *.h);;Executable Files (*.exe *.bin)"
        );

    if (!filePath.isEmpty()) {
        m_outputFilePath = filePath;
        outputFileLineEdit->setText(filePath);
        logMessage("Output file selected: " + filePath);
        processButton->setEnabled(true);
    }
}

void MainWindow::processFiles()
{
    if (m_inputFilePath.isEmpty() || m_outputFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select both input and output files!");
        return;
    }

    if (m_inputFilePath == m_outputFilePath) {
        QMessageBox::warning(this, "Error", "Input and output files cannot be the same!");
        return;
    }

    if (!QFile::exists(m_inputFilePath)) {
        QMessageBox::critical(this, "Error", "Input file does not exist!");
        return;
    }
    ptom_init();

    ptom_parse(m_outputFilePath,m_inputFilePath);
    logMessage("Starting deobfuscation process...");
    logMessage("Input: " + m_inputFilePath);
    logMessage("Output: " + m_outputFilePath);

    // Disable process button during operation
    processButton->setEnabled(false);

    // Process the files
    processDeobfuscation();

    // Re-enable process button
    processButton->setEnabled(true);
}

void MainWindow::processDeobfuscation()//implement here instead of in the object click
{
    try {
        // TODO: Replace this with your actual deobfuscation logic
        logMessage("Reading input file...");

        QFile inputFile(m_inputFilePath);
        if (!inputFile.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("Cannot open input file for reading");
        }

        QByteArray fileData = inputFile.readAll();
        inputFile.close();

        logMessage(QString("Read %1 bytes from input file").arg(fileData.size()));

        // Simulate deobfuscation process
        logMessage("Processing data...");

        // For now, just copy the file as a placeholder
        QFile outputFile(m_outputFilePath);
        if (!outputFile.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Cannot open output file for writing");
        }

        outputFile.write(fileData);
        outputFile.close();

        logMessage("Deobfuscation completed successfully!");
        logMessage(QString("Output written to: %1").arg(m_outputFilePath));

        QMessageBox::information(this, "Success",
                                 QString("Deobfuscation completed!\n\nOutput file: %1").arg(m_outputFilePath));

    } catch (const std::exception &e) {
        logMessage(QString("Error: %1").arg(e.what()));
        QMessageBox::critical(this, "Error",
                              QString("Deobfuscation failed:\n%1").arg(e.what()));
    }
}

void MainWindow::clearLog()
{
    logTextEdit->clear();
    logMessage("Log cleared.");
}

void MainWindow::logMessage(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString logEntry = QString("[%1] %2").arg(timestamp, message);

    logTextEdit->append(logEntry);

    // Auto-scroll to bottom
    QScrollBar *scrollBar = logTextEdit->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}
