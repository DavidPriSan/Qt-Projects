#include "charts.h"

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*
     * DIAGRAMA DE BARRAS
     */


    // Info Bar Chart
    QBarSet *set0 = new QBarSet("Altuve");
    QBarSet *set1 = new QBarSet("Martinez");
    QBarSet *set2 = new QBarSet("Segura");
    QBarSet *set3 = new QBarSet("Simmons");
    QBarSet *set4 = new QBarSet("Trout");

    *set0 << 283 << 341 << 313 << 338 << 346 << 335;
    *set1 << 250 << 315 << 282 << 307 << 303 << 330;
    *set2 << 294 << 246 << 257 << 319 << 300 << 325;
    *set3 << 248 << 244 << 265 << 281 << 278 << 313;
    *set4 << 323 << 287 << 299 << 315 << 306 << 313;

    // Asignar info al gráfico
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    //QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Batting Avg by Year");
    // Animaciones (NoAnimation, GridAxisAnimations, SeriesAnimations, AllAnimations)
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories; // Categorías Eje X
    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";
    QBarCategoryAxis *axis = new QBarCategoryAxis();

    // Ejes
    axis->append(categories);
    chart->createDefaultAxes();
    //chart->setAxisX(axis, series);
    chart->setAxisY(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Visualización
    QChartView *chartViewBar = new QChartView(chart);
    chartViewBar->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);


    /*
     * LINE CHART
     */


    // Info
    QLineSeries *seriesLine = new QLineSeries();
    seriesLine->append(0, 16);
    seriesLine->append(1, 25);
    seriesLine->append(2, 24);
    seriesLine->append(3, 19);
    seriesLine->append(4, 33);
    seriesLine->append(5, 25);
    seriesLine->append(6, 34);

    // Asignar info
    QChart *chartLine = new QChart();
    chartLine->legend()->hide();
    chartLine->addSeries(seriesLine);
    // Ejes
    chartLine->createDefaultAxes();

    QFont font; // Fuente
    font.setPixelSize(18);
    chartLine->setTitleFont(font);
    chartLine->setTitleBrush(QBrush(Qt::black));
    chartLine->setTitle("Barry Bonds HRs as Pirate");

    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    seriesLine->setPen(pen);

    chartLine->setAnimationOptions(QChart::AllAnimations); // Animación

    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("1986", 0);
    axisX->append("1987", 1);
    axisX->append("1988", 2);
    axisX->append("1989", 3);
    axisX->append("1990", 4);
    axisX->append("1991", 5);
    axisX->append("1992", 6);

    chartLine->setAxisX(axisX, series);

    QChartView *chartViewLine = new QChartView(chartLine);
    chartViewLine->setRenderHint(QPainter::Antialiasing);


    /*
     * PIE CHART
     */


    // Info
    QPieSeries *seriesPie = new QPieSeries();
    seriesPie->append("Vegetables", .40);
    seriesPie->append("Beans", .20);
    seriesPie->append("Fruit", .15);
    seriesPie->append("Seeds/Nuts", .10);
    seriesPie->append("Whole Grains", .15);

    // Labels para cada sector
    QPieSlice *slice0 = seriesPie->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice *slice1 = seriesPie->slices().at(1);
    slice1->setExploded(); // Para resaltar un sector (sale como separado)
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::darkGreen, 2)); // Borde
    slice1->setBrush(Qt::green); // Relleno

    QPieSlice *slice2 = seriesPie->slices().at(2);
    slice2->setLabelVisible();
    QPieSlice *slice3 = seriesPie->slices().at(3);
    slice3->setLabelVisible();
    QPieSlice *slice4 = seriesPie->slices().at(4);
    slice4->setLabelVisible();

    // Asignar info
    QChart *chartPie = new QChart();
    chartPie->addSeries(seriesPie);
    chartPie->setTitle("What Derek Ate that Week");
    chartPie->legend()->hide(); // No hace falta leyenda con las labels

    QChartView *chartViewPie = new QChartView(chartPie);
    chartViewPie->setRenderHint(QPainter::Antialiasing);


    /*
     * VENTANA
     */


    QMainWindow window;

    window.setCentralWidget(chartViewPie); // Visualizar gráfico en ventana (cambiar Bar/Line/Pie)
    window.resize(420, 300);
    window.show();

    return a.exec();
}
