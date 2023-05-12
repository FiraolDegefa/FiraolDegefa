#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QWidget>
#include <QtCharts/QLineSeries>
#include "authors.h"
#include "customtheme.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_USE_NAMESPACE

class ThemeWidget : public QWidget {
  Q_OBJECT
public:
  explicit ThemeWidget(QWidget *parent = 0);
  ~ThemeWidget();

private Q_SLOTS:
  void updateUI();

  void on_btnUpdate_clicked();

  void on_btnLoad_clicked();

  void on_btnExit_clicked();

  void on_pushButton_clicked();

private:
  DataTable generateRandomData(int listCount, int valueMax,
                               int valueCount) const;
  void populateThemeBox();
  void populateAnimationBox();
  void populateLegendBox();
  void connectSignals();

  QChart *createLineChart(QString name, DataTable dt) const;
  QChart *createCustomLineChart(QString name, DataTable dt) const;
  QChart *createCustomLineChart2(QString name, DataTable dt) const;
  QChart *createCustomLineChart3(QString name, DataTable dt) const;
  QChart *createSplineChart(QString name, DataTable dt) const;
  //    QChart *createScatterChart() const;
  //    QChart *createAreaChart() const;
  //    QChart *createBarChart(int valueCount) const;
  //    QChart *createPieChart() const;

private:
  int m_listCount;
  int m_valueMax;
  int m_valueCount;
  QList<QChartView *> m_charts;
  DataTable m_dataTable;
  Authors *authors;
  QLineSeries *createSinSeries();
  //    DataTable m_tempDataTable;

  Ui_ThemeWidgetForm *m_ui;
};

#endif /* THEMEWIDGET_H */
