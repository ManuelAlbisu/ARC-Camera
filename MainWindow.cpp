#include "MainWindow.h"

#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QLabel>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Camera Feed");

    // initialize camera
    QCamera *camera = new QCamera();

    // setup media capture session
    QMediaCaptureSession captureSession;
    captureSession.setCamera(camera);

    // create label to display video frames
    QLabel *videoLabel = new QLabel(this);
    videoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    videoLabel->setAlignment(Qt::AlignCenter);

    // create video sink
    QVideoSink *videoSink = new QVideoSink;
    captureSession.setVideoSink(videoSink);

    // connect video sink's newVideoFrame signal to slot that updates label
    QObject::connect(videoSink, &QVideoSink::videoFrameChanged, this, [&](const QVideoFrame &frame) {
        if (frame.isValid()) {
            QImage image = frame.toImage();
            videoLabel->setPixmap(QPixmap::fromImage(image));
        }
    });

    // set the label as the central widget of the window
    setCentralWidget(videoLabel);

    // start camera
    camera->start();
}

MainWindow::~MainWindow() { }
