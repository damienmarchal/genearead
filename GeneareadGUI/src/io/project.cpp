#include <header/io/project.h>
#include <header/image/imageManager.h>

#include <QFileDialog>
#include <QDebug>
#include <QQmlComponent>

static std::string GENEAREAD_VERSION = "GeneaRead1.0";
static std::string NEW_PROJECT = "New Project";
static std::string NO_FILE = "No File";

Project::Project(QQmlApplicationEngine* engine, ProjectReader* reader, ProjectWriter* writer, ImageManager* imageManager)
    : QObject(0)
{
    this->engine = engine;
    this->reader = reader;
    this->writer = writer;
    this->imageManager = imageManager;
    newProject();
}

ImageManager* Project::getImageManager() {
    return imageManager;
}

QObject* Project::findObject(QString name) {
    return engine->rootObjects().first()->findChild<QObject*>(name);
}

QObject* Project::createObject(QString filename, QString parent) {
    return createObject(filename, engine->rootObjects().first()->findChild<QObject*>(parent));
}

QObject* Project::createObject(QString filename, QObject* parent) {
    QQmlComponent* component = new QQmlComponent(
                engine,
                QUrl("qrc:/"+filename+".qml"),
                QQmlComponent::PreferSynchronous,
                parent);
    while(!component->isReady()) {
        if(component->isError()) {
            qDebug() << component->errors();
            return NULL;
        }
    }
    return component->create();
}

void Project::createLineIndex(cv::Rect& rect) {
    QObject* image = engine->rootObjects().first()->findChild<QObject*>("mainImage");
    QObject* object = PROJECT->createObject("LineIndex", image);
    qDebug() << image->children().at(0)->property("x");
    imageManager->createLine(rect, object, image);
}

std::string Project::toCString(QString qString) {
    return std::string(qString.toLatin1().data());
}

bool Project::readFile(QString filename) {
    std::string c_filename = toCString(filename);
    if(filename.endsWith(".genearead")) {
        read(reader, c_filename);
    } else {
        std::stringstream ss;
        ss << NEW_PROJECT << " (" << c_filename << ")";
        setProjectName(ss.str());

        imageName = c_filename;
        imageManager->loadFile(filename);
    }
    return true;
}

void Project::newProject() {
    version = GENEAREAD_VERSION;
    setProjectName(NEW_PROJECT);
    imageName = NO_FILE;
}

void Project::setProjectName(std::string name) {
    projectName = name;
    QGuiApplication::setApplicationDisplayName(qPrintable(QString::fromStdString(name)));
}

void Project::read(ProjectReader* reader, std::string filename) {
    if(!reader->open(filename))
        return;
    version     = reader->readString();
    projectName = reader->readString();
    imageName   = reader->readString();
    imageManager->read(reader);
    if(!reader->close()) {
        qDebug() << "Waring : closing";
    }
}

bool Project::writeFile(QString filename) {
    write(writer, toCString(filename));
    return true;
}

void Project::write(ProjectWriter* writer, std::string filename) {
    if(!writer->open(filename))
        return;
    writer->writeString(version);
    writer->writeChar(0);
    writer->writeString(projectName);
    writer->writeChar(0);
    writer->writeString(imageName);
    writer->writeChar(0);
    imageManager->write(writer);
    if(!writer->close()) {
        qDebug() << "Waring : closing";
    }
}




static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    /*static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations =
                QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

        dialog.setDirectory(
                    picturesLocations.isEmpty()
                    ? QDir::currentPath()
                    : picturesLocations.last()
                      );
    }*/

    QStringList mimeTypeFilters;
    /*const QByteArrayList supportedMimeTypes =
            acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes()
            : QImageWriter::supportedMimeTypes();

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);*/

    mimeTypeFilters.append("application/octet-stream");
    mimeTypeFilters.append("image/png");

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    //dialog.selectMimeTypeFilter("image/png");
    dialog.selectMimeTypeFilter("application/octet-stream");

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("png");
}

static void initializeGeneaReadFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode) {

    /*QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes =
            acceptMode == QFileDialog::AcceptOpen
            ? QImageReader::supportedMimeTypes()
            : QImageWriter::supportedMimeTypes();

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);*/
    dialog.selectMimeTypeFilter("genearead");

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("genearead");
}

void Project::open() {
    QFileDialog dialog(QApplication::activeWindow(), tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (
           dialog.exec() == QDialog::Accepted &&
           !readFile(dialog.selectedFiles().first())
           ) {
        qDebug() << "dialog opened at "+ dialog.selectedFiles().first();
    }
}

void Project::close() {
    newProject();
    imageManager->reset();
}

void Project::saveAs() {
    QFileDialog dialog(QApplication::activeWindow(), tr("Save File As"));
    initializeGeneaReadFileDialog(dialog, QFileDialog::AcceptSave);

    while (
           dialog.exec() == QDialog::Accepted &&
           !writeFile(dialog.selectedFiles().first())
           ) {}
}
