#ifndef LIVETIKZ_H
#define LIVETIKZ_H

#include <QMenuBar>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QScrollArea>
#include <QSettings>
#include <QSplitter>
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QTextEdit>
#include <QTextCursor>
#include <QTimer>
#include <KParts/MainWindow>
#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <poppler-qt5.h>
#include <ZoomScrollImage.h>

class MainWindow : public KParts::MainWindow {
  Q_OBJECT
public:
  MainWindow();
  virtual ~MainWindow();

public slots:
  void load(const QUrl &url);
  void load();
  void textChanged(KTextEditor::Document *document);
  void refresh();
  void browse();
  void render(double scale);
  void renderFinished(int code);
  void renderFailed(QProcess::ProcessError);
  void showCompilerSelection();
  void updateLog();
  void gotoPreviousImage();
  void gotoNextImage();
  void updateTemplate(const QString& filename);

private:
  void setupActions();
  void setupMenu();
  void setupUI();
  void setupEditor();

  void render();
  void compile();
  
  void appendLog(QString str);


  QWidget *window;
  QSplitter *splitView;
  QHBoxLayout *mainLayout;
  QHBoxLayout *templateLayout;
  QHBoxLayout *logLayout;
  QSpacerItem *spacerItem;
  QVBoxLayout *leftLayout;

  KParts::ReadWritePart *katePart;
  KTextEditor::View *view;
  KTextEditor::Document *doc;
  ZoomScrollImage *display;
  QFileInfo texdir;
  QTemporaryDir* dir;
  Poppler::Document *currentDoc;

  QTimer *refreshTimer;
  QTimer *renderTimer;

  QTextEdit *log;

  QUrl templateFile;
  QLineEdit *templateLabel;
  QPushButton *browseButton;

  QPushButton* killButton;
  
  QProcess *renderProcess;
  QString renderOutput;
  
  QAction* nextImage;
  QAction* prevImage;
  
  int currentPage;
};

#endif
