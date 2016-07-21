#ifndef USERSMODEL_H
#define USERSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QHostAddress>

struct Users {
    QHostAddress address;
    QString userName;
    QByteArray hash;
};

class UsersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum UsersRoles {
        UserNameRole = Qt::UserRole + 1,
        HashRole,
        AddressRole
    };

    UsersModel(QObject *parent = 0);

    void addUser(const QString &name, const QString &password);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Users> m_users;
};

#endif // USERSMODEL_H
