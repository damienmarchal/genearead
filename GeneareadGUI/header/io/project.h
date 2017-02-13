#ifndef PROJECT_H
#define PROJECT_H

#include <header/io/projectReader.h>
#include <header/io/projectWriter.h>

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include <QtWidgets>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QFileDialog>

class Project : public QObject
{
    Q_OBJECT

public:
    /**
      * @brief open
      * Opens a dialog to load a file.
      */
    Q_INVOKABLE void open();

    /**
      * @brief close
      * Close current project.
      * EEffectively loads a new empty project instead.
      */
    Q_INVOKABLE void close();

    /**
      * @brief saveAs
      * Open a dialog to save a file.
      */
    Q_INVOKABLE void saveAs();

    /**
      * @brief findObject
      * @note this Q_INVOKABLE is unused
      * @param name the object's <code>objectName</code> property
      * @return a pointer to the object named <code>objectName</code>.
      * If such an object does not exist returns a QObject pointing to NULL.
      */
    Q_INVOKABLE QObject* findObject(QString name);

    Project(QQmlApplicationEngine* engine, ProjectReader* reader, ProjectWriter* writer, ImageManager* imageManager);

    ImageManager* getImageManager();

    /**
     * @brief read
     * Reads project data from a file.
     * @param reader the reader used to parse the project data.
     * @param filename the local file name.
     */
    void read(ProjectReader* reader, std::string filename);

    /**
     * @brief readFile
     * Reads a filename to decide how to parse it according to its extension.
     * Can read ".genearead" and ".png" files.
     * @param filename the local file name.
     * @return true.
     */
    bool readFile(QString filename);

    /**
     * @brief write
     * Writes project data to a file.
     * @param writer the writer used to add the project data.
     * @param filename the local file name.
     */
    void write(ProjectWriter* writer, std::string filename);

    /**
     * @brief writeFile
     * Writes a project to a file.
     * @param filename the local file name.
     * @return true.
     */
    bool writeFile(QString filename);

    /**
     * @brief newProject
     * Loads a new empty project.
     */
    void newProject();

    /**
     * @brief setProjectName
     * Sets the name of the project.
     * Modifies the application display name for the Qt window.
     * @todo does not actually change the display name.
     * @param name the new project name.
     */
    void setProjectName(std::string name);

    /**
     * @brief toCString
     * Converts a QString to a c std::string.
     * @param qString the QString to convert.
     * @return an equivalent std::string.
     */
    std::string toCString(QString qString);

    /**
     * @brief createObject
     * Creates a QObject from a ".qml" model file.
     * @param filename the ".qml" model file.
     * @param parent the parent of the created object.
     * @return the created QObject.
     */
    QObject* createObject(QString filename, QObject* parent);

    /**
     * @brief createObject
     * Creates a QObject from a ".qml" model file.
     * @param filename the ".qml" model file.
     * @param parent the parent's "objectName" property.
     * @return the created QObject.
     */
    QObject* createObject(QString filename, QString parent);

    /**
     * @brief createLineIndex
     * Creates a line object used by the ImageManager.
     * @todo adds support for line objects in the ImageManger.
     * @param rect the bounding box of the line.
     */
    void createLineIndex(cv::Rect& rect);

protected:

private:
    QQmlApplicationEngine* engine;
    ProjectReader* reader;
    ProjectWriter* writer;
    ImageManager* imageManager;

    std::string version;
    std::string projectName;
    std::string imageName;
    long lastSave;
};

extern Project* PROJECT;

#endif // PROJECT_H
