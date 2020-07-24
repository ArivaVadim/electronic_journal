#include "api.h"

API::API()
{
    _host = "www.lubimaya.by";
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
    //connect(APIobject, SIGNAL(done()), this, SLOT(getReplyData()));    //использовать вне класса
}

API::~API()
{
    delete manager;
}

void API::setSqlQuery(QSqlQuery &q)
{
    this->q=q;
}

void API::initDataForRequest(const QString &tableName, const int &id)
{
    //формирует данные для формирования запроса на сервер по полученному id из выбранной таблицы

    if(!tableNameError(tableName))
    {
        q.exec("SELECT * FROM '"+tableName+"'");
        int count = q.record().count();
        QString *fieldName = new QString [count];   //array of keys
        QString *value = new QString [count];       //array of values

        QString ID;
        ID.setNum(id);

        q.exec("SELECT * FROM '"+tableName+"' WHERE id ="+ID);
        for (int i=0;i<count;i++)
        {
            fieldName[i] = q.record().fieldName(i);
            //qDebug()<<fieldName[i];
        }

        while (q.next())
        {
            for (int i=0;i<count;i++)
            {
                value[i] = q.value(i).toString();
                //qDebug()<<value[i];
            }
        }

        for(int i=0;i<count;i++)
            _data.insert(fieldName[i],value[i]);

        //qDebug()<<_data;

        delete [] value;
        delete [] fieldName;
    }
}

void API::setRequest(const QString &tableName, const QString &operation)
{
    //request with _data
    //operations: delete, insert, read, update

    qDebug()<<"setRequest "+operation+" to "+tableName;

    if(!tableNameError(tableName)&&!operationNameError(operation))
    {
        QUrl url;
        url.setScheme("http");
        url.setHost(_host);
        url.setPath("/api/"+tableName+"/"+operation+".php");

        QNetworkRequest request;
        request.setUrl(url);
        request.setRawHeader("Content-Type","application/json");

        QByteArray dataByteArray = variantMapToJson(_data);
        manager->post(request,dataByteArray);

        qDebug()<<request.url();
    }
}

void API::setRequest(const QString &tableName, const QString &operation, QVariantMap &data)
{
    //request with data
    //operations: delete, insert, read, update

    qDebug()<<"setRequest "+operation+" to "+tableName;

    if(!tableNameError(tableName)&&!operationNameError(operation))
    {
        QUrl url;
        url.setScheme("http");
        url.setHost(_host);
        url.setPath("/api/"+tableName+"/"+operation+".php");

        QNetworkRequest request;
        request.setUrl(url);
        request.setRawHeader("Content-Type","application/json");

        QByteArray dataByteArray = variantMapToJson(data);
        manager->post(request,dataByteArray);

        qDebug()<<request.url();
    }
}

void API::readAllFromTable(const QString &tableName)
{
    qDebug()<<"read all from "+tableName;

    if(!tableNameError(tableName))
    {
        QUrl url;
        url.setScheme("http");
        url.setHost(_host);
        url.setPath("/api/"+tableName+"/read.php");

        QNetworkRequest request;
        request.setUrl(url);
        manager->get(request);
        qDebug()<<request.url();
    }
}

void API::getReply(QNetworkReply *reply)
{
    qDebug()<<"getReply";

    reply -> waitForReadyRead(1000);

    jsonDocument = QJsonDocument::fromJson(reply->readAll(),&jsonError);

    if(jsonError.errorString()=="no error occurred")
    {
        _replyData = jsonToVariantMap(jsonDocument);
        qDebug()<<"jsonDocument"<<jsonDocument;
        emit done();
    }
    else
    {
        qDebug()<<"Error: "<<jsonError.errorString();
    }
    reply->deleteLater();
}

QVariantMap API::getReplyData()
{
    qDebug()<<"getReplyData";
    return _replyData;
}

QByteArray API::variantMapToJson(QVariantMap &data)
{
    QJsonDocument postDataDoc = QJsonDocument::fromVariant(data);
    QByteArray dataByteArray = postDataDoc.toJson();
    return dataByteArray;
}

QVariantMap API::jsonToVariantMap(QJsonDocument &replyData)
{
    QVariantMap data = replyData.toVariant().toMap();
    return data;
}

QVariantMap API::getRequestData()
{
    return _data;
}

void API::clearRequestData()
{
    _data.clear();
}

void API::setRequestData(QVariantMap &data)
{
    _data=data;
}

bool API::tableNameError(const QString &tableName)
{
    qDebug()<<"check on tableNameError";

    if(tableName=="client")
        return false;
    else if(tableName=="workefftable")
        return false;
    else if(tableName=="service")
        return false;
    else if(tableName=="cat_service")
        return false;
    else if(tableName=="policity_discont")
        return false;
    else if(tableName=="discont")
        return false;
    else if(tableName=="setting")
        return false;
    else if(tableName=="timetable_salon")
        return false;
    else if(tableName=="cat_masters")
        return false;
    else
    {
        qDebug()<<"Error of TABLE name!";
        return true;
    }

}

bool API::operationNameError(const QString &operation)
{
    qDebug()<<"check on operationNameError";

    if(operation=="delete")
        return false;
    else if(operation=="insert")
        return false;
    else if(operation=="read")
        return false;
    else if(operation=="update")
        return false;
    else
    {
        qDebug()<<"Error of OPERATION name!";
        return true;
    }
}

void API::setHost(QString &host)
{
    _host = host;
}

QString API::getHost()
{
    return _host;
}
