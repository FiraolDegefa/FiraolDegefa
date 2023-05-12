#include "themewidget.h"
#include "ui_themewidget.h"

#include <QDebug>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QFileDialog>

ThemeWidget::ThemeWidget(QWidget *parent)
    : QWidget(parent), m_listCount(3), m_valueMax(10), m_valueCount(7),
      m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
      //m_tempDataTable(generateRandomData(m_listCount, m_valueMax,
      //m_valueCount)),

  m_ui(new Ui_ThemeWidgetForm) {
  m_ui->setupUi(this);
  populateThemeBox();
  populateAnimationBox();
  populateLegendBox();

  // create charts

  QChartView *chartView;

  chartView = new QChartView(createLineChart("Graph A", m_dataTable));
  m_ui->gridLayout->addWidget(chartView, 1, 0);
  m_charts << chartView;

  chartView = new QChartView(createSplineChart("Spline Graph", generateRandomData(3, 10, 10)));
  m_ui->gridLayout->addWidget(chartView, 1, 1);
  m_charts << chartView;

  chartView =
      new QChartView(createCustomLineChart3("Graph C", generateRandomData(2, 2, 9)));
  m_ui->gridLayout->addWidget(chartView, 2, 0);
  m_charts << chartView;

  chartView =
      new QChartView(createCustomLineChart("Graph D", generateRandomData(3, 25, 25)));
  m_ui->gridLayout->addWidget(chartView, 2, 1);
  m_charts << chartView;

  chartView = new QChartView(createCustomLineChart2("Graph E", generateRandomData(4, 35, 35)));
  m_ui->gridLayout->addWidget(chartView, 3, 0);
  m_charts << chartView;

  chartView = new QChartView(createCustomLineChart2("Graph F", generateRandomData(2, 7, 35)));
  m_ui->gridLayout->addWidget(chartView, 3, 1);
  m_charts << chartView;



  // Set defaults
  m_ui->antialiasCheckBox->setChecked(true);

  // Set the colors from the light theme as default ones
  QPalette pal = qApp->palette();
  pal.setColor(QPalette::Window, QRgb(0xADD8E6));
  pal.setColor(QPalette::WindowText, QRgb(0x00008B));
  qApp->setPalette(pal);

  updateUI();
}

ThemeWidget::~ThemeWidget() { delete m_ui; }

DataTable ThemeWidget::generateRandomData(int listCount, int valueMax,
                                          int valueCount) const {
  DataTable dataTable;

  // generate random data
    for (int i(0); i < listCount; i++) {
      DataList dataList;
      qreal yValue(-10);
      for (int j(-10); j < valueCount; j++) {
        yValue = yValue + QRandomGenerator::global()->bounded(valueMax /
                                                              (qreal)valueCount);
        QPointF value((j + QRandomGenerator::global()->generateDouble()) *
                          ((qreal)m_valueMax / (qreal)valueCount),
                      yValue);
        QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
        dataList << Data(value, label);
      }
      dataTable << dataList;
    }

  return dataTable;
}

void ThemeWidget::populateThemeBox() {
  // add items to theme combobox
  m_ui->themeComboBox->addItem("Theme-1", 8);
  m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
  m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
  m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
  m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
  m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
  m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
  m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
  m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox() {
  // add items to animation combobox
  m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
  m_ui->animatedComboBox->addItem("GridAxis Animations",
                                  QChart::GridAxisAnimations);
  m_ui->animatedComboBox->addItem("Series Animations",
                                  QChart::SeriesAnimations);
  m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void ThemeWidget::populateLegendBox() {
  // add items to legend combobox
  m_ui->legendComboBox->addItem("No Legend ", 0);
  m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
  m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
  m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
  m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}


QChart *ThemeWidget::createCustomLineChart(QString name, DataTable dt) const {

  QChart *chart = new QChart();
  chart->setTitle(name);




  // Set custom font
  QFont font;
  font.setPixelSize(18);
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(25);
  chart->setTitleFont(font);

  // Customize series
  QPen pen(QRgb(0x008000));
  pen.setWidth(1);

  QString sname("LAB ");
  int nameIndex = 0;
  for (const DataList &list : dt) {
    QLineSeries *series = new QLineSeries(chart);
    qreal step = 0.1;
    qreal x = -10.0;
    while (x <= 10.0) {
        series->append(x, qSin(x));
        x += step;
    }
    series->setName(sname + QString::number(nameIndex));
    series->setPen(pen);
    nameIndex++;
    chart->addSeries(series);
  }

  chart->createDefaultAxes();
  chart->axes(Qt::Horizontal).first()->setRange(-10, m_valueMax);
  chart->axes(Qt::Vertical).first()->setRange(-10, m_valueCount);

  // Add space to label to add space between labels and axis
  QValueAxis *axisY =
      qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
  Q_ASSERT(axisY);
  axisY->setLabelFormat("%.1f  ");

  return chart;
}

QChart *ThemeWidget::createCustomLineChart2(QString name, DataTable dt) const {

  QChart *chart = new QChart();
  chart->setTitle(name);




  // Set custom font
  QFont font;
  font.setPixelSize(18);
  font.setWeight(QFont::ExtraBold);
  font.setPixelSize(25);
  chart->setTitleFont(font);

  // Customize series
  QPen pen(QRgb(0x008000));
  pen.setWidth(1);

  QString sname("LAB ");
  int nameIndex = 0;
  for (const DataList &list : dt) {
    QLineSeries *series = new QLineSeries(chart);
    qreal step = 0.1;
    qreal x = -10.0;
    while (x <= 10.0) {
        series->append(x, qCos(x));
        x += step;
    }
    series->setName(sname + QString::number(nameIndex));
    series->setPen(pen);
    nameIndex++;
    chart->addSeries(series);
  }

  chart->createDefaultAxes();
  chart->axes(Qt::Horizontal).first()->setRange(-10, m_valueMax);
  chart->axes(Qt::Vertical).first()->setRange(-10, m_valueCount);

  // Add space to label to add space between labels and axis
  QValueAxis *axisY =
      qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
  Q_ASSERT(axisY);
  axisY->setLabelFormat("%.1f  ");

  return chart;
}

QChart *ThemeWidget::createCustomLineChart3(QString name, DataTable dt) const {

  QChart *chart = new QChart();
  chart->setTitle(name);




  // Set custom font
  QFont font;
  font.setPixelSize(18);
  chart->setTitleFont(font);

  // Customize series
  QPen pen(QRgb(0x008000));
  pen.setWidth(1);

  QString sname("LAB ");
  int nameIndex = 0;
  for (const DataList &list : dt) {
    QLineSeries *series = new QLineSeries(chart);
    qreal step = 0.1;
    qreal x = -10.0;
    while (x <= 10.0) {
        series->append(x, qTan(x));
        x += step;
    }
    series->setName(sname + QString::number(nameIndex));
    series->setPen(pen);
    nameIndex++;
    chart->addSeries(series);
  }

  chart->createDefaultAxes();
  chart->axes(Qt::Horizontal).first()->setRange(-10, m_valueMax);
  chart->axes(Qt::Vertical).first()->setRange(-10, m_valueCount);

  // Add space to label to add space between labels and axis
  QValueAxis *axisY =
      qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
  Q_ASSERT(axisY);
  axisY->setLabelFormat("%.1f  ");

  return chart;
}

QChart *ThemeWidget::createLineChart(QString name, DataTable dt) const {

  QChart *chart = new QChart();
  chart->setTitle(name);

  QString sname("Covid");
  int nameIndex = 0;
  for (const DataList &list : dt) {
    QLineSeries *series = new QLineSeries(chart);
    for (const Data &data : list)
      series->append(data.first);
    series->setName(sname + QString::number(nameIndex));
    nameIndex++;
    chart->addSeries(series);
  }

  chart->createDefaultAxes();
  chart->axes(Qt::Horizontal).first()->setRange(-10, m_valueMax);
  chart->axes(Qt::Vertical).first()->setRange(-10, m_valueCount);

  // Add space to label to add space between labels and axis
  QValueAxis *axisY =
      qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
  Q_ASSERT(axisY);
  axisY->setLabelFormat("%.1f  ");

  return chart;
}


QChart *ThemeWidget::createSplineChart(QString name, DataTable dt) const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString sname("Series ");
    int nameIndex = 0;
    for (const DataList &list : dt) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(-10, m_valueMax);
    chart->axes(Qt::Vertical).first()->setRange(-10, m_valueCount);

    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}

void ThemeWidget::updateUI() {

  QChart::ChartTheme theme = static_cast<QChart::ChartTheme>(
      m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex())
          .toInt());

  const auto charts = m_charts;
  if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
    for (QChartView *chartView : charts) {

      chartView->chart()->setTheme(theme);
    }

    // Set palette colors based on selected theme

    QPalette pal = window()->palette();
    if (theme == 8) {
      pal.setColor(QPalette::Window, QRgb(0xADD8E6));
      pal.setColor(QPalette::WindowText, QRgb(0x00008B));
    } else if (theme == QChart::ChartThemeLight) {
      pal.setColor(QPalette::Window, QRgb(0xf0f0f1));
      pal.setColor(QPalette::WindowText, QRgb(0x304033));
    } else if (theme == QChart::ChartThemeDark) {
      pal.setColor(QPalette::Window, QRgb(0x121218));
      pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    } else if (theme == QChart::ChartThemeBlueCerulean) {
      pal.setColor(QPalette::Window, QRgb(0x20422a));
      pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    } else if (theme == QChart::ChartThemeBrownSand) {
      pal.setColor(QPalette::Window, QRgb(0x9e8965));
      pal.setColor(QPalette::WindowText, QRgb(0x604066));
    } else if (theme == QChart::ChartThemeBlueNcs) {
      pal.setColor(QPalette::Window, QRgb(0x018bba));
      pal.setColor(QPalette::WindowText, QRgb(0x704077));
    } else if (theme == QChart::ChartThemeHighContrast) {
      pal.setColor(QPalette::Window, QRgb(0xffab03));
      pal.setColor(QPalette::WindowText, QRgb(0x151518));
    } else if (theme == QChart::ChartThemeBlueIcy) {
      pal.setColor(QPalette::Window, QRgb(0xcee7f0));
      pal.setColor(QPalette::WindowText, QRgb(0x704077));
    } else {
      pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
      pal.setColor(QPalette::WindowText, QRgb(0x4604044));
    }
    window()->setPalette(pal);
  }

  // Update antialiasing

  bool checked = m_ui->antialiasCheckBox->isChecked();
  for (QChartView *chart : charts)
    chart->setRenderHint(QPainter::Antialiasing, checked);

  // Update animation options

  QChart::AnimationOptions options(
      m_ui->animatedComboBox->itemData(m_ui->animatedComboBox->currentIndex())
          .toInt());
  if (!m_charts.isEmpty() &&
      m_charts.at(0)->chart()->animationOptions() != options) {
    for (QChartView *chartView : charts)
      chartView->chart()->setAnimationOptions(options);
  }

  // Update legend alignment

  Qt::Alignment alignment(
      m_ui->legendComboBox->itemData(m_ui->legendComboBox->currentIndex())
          .toInt());

  if (!alignment) {
    for (QChartView *chartView : charts)
      chartView->chart()->legend()->hide();
  } else {
    for (QChartView *chartView : charts) {
      chartView->chart()->legend()->setAlignment(alignment);
      chartView->chart()->legend()->show();
    }
  }
}

void ThemeWidget::on_btnUpdate_clicked() {
    m_dataTable = generateRandomData(m_listCount, m_valueMax, m_valueCount);

    for(int i =0; i< 2; i++){

        QChartView *chartView = m_charts.at(i);

        QChart *chart = chartView->chart();

        QList<QAbstractSeries*> existingSeries = chart->series();
        foreach(QAbstractSeries* series, existingSeries) {
            chart->removeSeries(series);
            delete series;
        }

        QLineSeries *series = new QLineSeries(chart);
        for (const DataList &list : m_dataTable) {
          QLineSeries *series = new QLineSeries(chart);
          for (const Data &data : list)
            series->append(data.first);
          chart->addSeries(series);
        }

    }



}

void ThemeWidget::on_btnLoad_clicked() {
    authors = new Authors(this);
    authors -> show();
}

void ThemeWidget::on_btnExit_clicked() { QCoreApplication::quit(); }

void ThemeWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), QDir::homePath(), tr("CSV Files (*.csv)"));
        if (fileName.isEmpty()) {
            return;
        }

        // Open the CSV file and read the data into a QVector
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file" << fileName;
            return;
        }
        QVector<QPointF> data;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() != 2) {
                qWarning() << "Invalid line in CSV file:" << line;
                continue;
            }
            double x = fields[0].toDouble();
            double y = fields[1].toDouble();
            data.append(QPointF(x, y));
        }

        QLineSeries *series = new QLineSeries();
        QChartView *chartView = m_charts.at(1);

        QChart *chart = chartView->chart();

        QList<QAbstractSeries*> existingSeries = chart->series();
        foreach(QAbstractSeries* series, existingSeries) {
            chart->removeSeries(series);
            delete series;
        }
        series->append(data);
        chart->addSeries(series);
}

