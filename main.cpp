#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

class TextEditor : public QMainWindow {
public:
    TextEditor() {
        // 创建菜单栏
        QMenu* fileMenu = menuBar()->addMenu(tr("File"));

        // 创建菜单项
        QAction* openAction = new QAction(tr("Open"), this);
        QAction* saveAction = new QAction(tr("Save"), this);

        // 将菜单项添加到菜单栏
        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);

        // 连接信号和槽
        connect(openAction, &QAction::triggered, this, &TextEditor::openFile);
        connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile);

        // 创建文本编辑器
        QTextEdit* textEdit = new QTextEdit(this);
        setCentralWidget(textEdit);
    }

    void openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Text Files (*.txt);;All Files (*.*)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                ((QTextEdit*)centralWidget())->setPlainText(stream.readAll());
                file.close();
            }
        }
    }

    void saveFile() {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Text Files (*.txt);;All Files (*.*)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << ((QTextEdit*)centralWidget())->toPlainText();
                file.close();
            }
        }
    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // 初始化 Qt 库
    if (!QCoreApplication::instance()) {
        new QApplication(argc, argv);
    }

    TextEditor textEditor;
    textEditor.show();

    // 运行 Qt 应用程序
    return QApplication::exec();
}
