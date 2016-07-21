#include "usersmodel.h"
#include <QCryptographicHash>

UsersModel::UsersModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void UsersModel::addUser(const QString &name, const QString &password)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Users users;
    users.userName = name;
    users.hash = QCryptographicHash::hash(QByteArray(name.toUtf8() + password.toUtf8()),
                                          QCryptographicHash::Sha1);
    m_users.append(users);
    endInsertRows();
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    m_users.count();
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_users.count())
        return QVariant();

    const Users &user = m_users[index.row()];
    if (role == UserNameRole)
        return user.userName;
    else if (role == HashRole)
        return user.hash;
    else if (role == AddressRole)
        return user.address.toString();
    return QVariant();

}


QHash<int, QByteArray> UsersModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[UserNameRole] = "username";
    roles[HashRole] = "hash";
    roles[AddressRole] = "address";
    return roles;
}
