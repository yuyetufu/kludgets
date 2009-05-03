#ifndef KLUDGET_H
#define KLUDGET_H

#include <QTimer>
#include <QMenu>
#include <QSignalMapper>

#include "kludgetinfo.h"
#include "version.h"

class KClient;
class KWindow;
class KView;
class KPage;
class KSystem;
class KSettings;
class AboutWindow;
class PreferenceWindow;

class QWebFrame;
class QMenu;

class Kludget : public QObject
{
    Q_OBJECT

public:

    Kludget(KClient *client = 0);
    ~Kludget();
    static Kludget* create(KClient *client, const KludgetInfo &info);

private:
    bool loadSettings(const KludgetInfo &info, bool loadPage = false);
    bool loadPreferences(const QString &path);
    void saveSettings();
    void addJavaScriptWindowObjects(QWebFrame* frame);
    void runJavaScriptFile(QWebFrame* frame, const QString &);
    void setupContextMenu();
    void loadMenuFile(const QString &);

    private
Q_SLOTS:

    void onBeginShowCountDown();
    void onShow();
    void onHide();
    void onStartDrag();
    void onEndDrag();
    void onRemove();
    void onSettingsChanged();
    void onEvaluate(const QString &);
    void onWindowDestroyed();
    void onPreferencesClosed();
    void onContextMenu();
    void onJavaScriptWindowObjectCleared();
    void onFrameCreated(QWebFrame*);
    void onUrlReceived(const QUrl*);
    void onSystemExecUpdate(long id);
    void onSystemExecFinish(long id);

private:

    KludgetInfo info;

    KClient *client;
    KWindow *window;
    KView *view;
    KPage *page;
    KSystem *system;

    bool firstShow;

    PreferenceWindow *prefWindow;
    AboutWindow *aboutWindow;

    QSignalMapper customMenuMapper;
    QMenu contextMenu;

public:

    KSettings *settings;

    public
Q_SLOTS:
    void show();
    void hide();
    void close();
    void inspect();
    void reload();
    void about();
    void configure(QString cat = "");
    void createInstance();
    void move(int x, int y);
    void resize(int w, int h);
    int opacity();
    int windowLevel();
    int x();
    int y();
    int width();
    int height();
    void renderLayer(QString layer);
    void prepareForTransition(QString transition);
    void performTransition();

Q_SIGNALS:
    void evaluate(const QString &);

};

#endif
