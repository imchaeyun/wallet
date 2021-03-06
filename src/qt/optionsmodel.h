// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSMODEL_H
#define BITCOIN_QT_OPTIONSMODEL_H

#include "amount.h"

#include <QAbstractListModel>

QT_BEGIN_NAMESPACE
class QNetworkProxy;
QT_END_NAMESPACE

/** Interface from Qt to configuration data structure for Bitcoin client.
   To Qt, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit OptionsModel(QObject *parent = 0, bool resetSettings = false);

    enum OptionID {
        StartAtStartup,         // bool
        HideTrayIcon,           // bool
        MinimizeToTray,         // bool
        MapPortUPnP,            // bool
        MinimizeOnClose,        // bool
        ProxyUse,               // bool
        ProxyIP,                // QString
        ProxyPort,              // int
        ProxyUseTor,            // bool
        ProxyIPTor,             // QString
        ProxyPortTor,           // int
        DisplayUnit,            // BitcoinUnits::Unit
        ThirdPartyTxUrls,       // QString
        Language,               // QString
        Theme,                  // QString
        MiningPool,             // QString
        MinerPath,              // QString
        MinerExtraParams,       // QString
        MinerStartUp,           // bool
        MiningUsername,         // QString
        MiningPassword,         // QString
        CoinControlFeatures,    // bool
        ThreadsScriptVerif,     // int
        DatabaseCache,          // int
        SpendZeroConfChange,    // bool
        Listen,                 // bool
        OptionIDRowCount,
    };

    void Init(bool resetSettings = false);
    void Reset();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    /** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
    void setDisplayUnit(const QVariant &value);
    void setTheme(const QVariant &value);
    void setMiningPool(const QVariant &value);
    void setMiningUsername(const QVariant &value);
    void setMiningPassword(const QVariant &value);
    void setMinerPath(const QVariant &value);
    void setMinerExtraParams(const QVariant &value);
    void setMinerStartUp(const QVariant &value);

    /* Explicit getters */
    bool getHideTrayIcon() { return fHideTrayIcon; }
    bool getMinimizeToTray() { return fMinimizeToTray; }
    bool getMinimizeOnClose() { return fMinimizeOnClose; }
    int getDisplayUnit() { return nDisplayUnit; }
    QString getTheme() { return theme; }
    QString getThirdPartyTxUrls() { return strThirdPartyTxUrls; }
    bool getProxySettings(QNetworkProxy& proxy) const;
    bool getCoinControlFeatures() { return fCoinControlFeatures; }
    const QString& getOverriddenByCommandLine() { return strOverriddenByCommandLine; }

    /* Miner */
    QString getMiningPool() { return miningPool; }
    QString getMiningUsername() { return miningUsername; }
    QString getMiningPassword() { return miningPassword; }
    QString getMinerPath() { return minerPath; }
    QString getMinerExtraParams() { return minerExtraParams; }
    bool getMinerStartUp() { return minerStartUp; }

    /* Restart flag helper */
    void setRestartRequired(bool fRequired);
    bool isRestartRequired();

private:
    /* Qt-only settings */
    bool fHideTrayIcon;
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    QString language;
    QString theme;
    QString miningPool;
    QString minerPath;
    QString miningUsername;
    QString miningPassword;
    QString minerExtraParams;
    bool minerStartUp;
    int nDisplayUnit;
    QString strThirdPartyTxUrls;
    bool fCoinControlFeatures;
    /* settings that were overriden by command-line */
    QString strOverriddenByCommandLine;

    // Add option to list of GUI options overridden through command line/config file
    void addOverriddenOption(const std::string &option);

    // Check settings version and upgrade default values if required
    void checkAndMigrate();
Q_SIGNALS:
    void displayUnitChanged(int unit);
    void themeChanged(QString theme);
    void miningPoolChanged(QString miningPool);
    void miningUsernameChanged(QString miningUsername);
    void miningPasswordChanged(QString miningPassword);
    void minerPathChanged(QString minerPath);
    void minerExtraParamsChanged(QString minerExtraParams);
    void minerStartUpChanged(bool minerStartUp);
    void coinControlFeaturesChanged(bool);
    void hideTrayIconChanged(bool);
};

#endif // BITCOIN_QT_OPTIONSMODEL_H
