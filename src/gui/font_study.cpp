#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QFontInfo>
#include <QFontMetrics>
#include <QGuiApplication>

void TestFontCreation() {
  // Font families �ɲμ� QFont::StyleHint.

  QFont f1("SansSerif");
  qInfo() << f1.family();
  // "SansSerif"
  // ���õ���ʲô�����ؾ���ʲô

  qInfo() << QFontInfo(f1).family();
  // "MS Shell Dlg 2"
  // QFontInfo ����ʵ�ʵ�������Ϣ

  QFont f2("Monospace", 10, QFont::Bold);
  qInfo() << QFontInfo(f2).family();
  // "MS Shell Dlg 2"

  // ��Ȼ������ family������Ҳ���Դ� facename
  // Qt ���� wxWidgets��������û�� facename ����˵��
  QFont f3("Verdana", 10, QFont::Bold);
  qInfo() << QFontInfo(f3).family();
  // "Verdana"
  QFont f4("Consolas", 10, QFont::Bold);
  qInfo() << QFontInfo(f4).family();
  // "Consolas"
}

void TestFontDatabase() {
  QFontDatabase database;

  // ö��ϵͳ�������

  for (const QString& family : database.families()) {
    qInfo() << family;  // ��ʵ�� facename

    for (const QString& style : database.styles(family)) {
      QString sizes;
      for (int points : database.smoothSizes(family, style)) {
        sizes += QString::number(points) + ' ';
      }
      qInfo() << "  " << sizes.trimmed();
    }
  }
}

void TestFontMetrics() {
  QFont font("Consolas", 10);

  QFontMetrics metrics(font);

  // horizontalAdvance: Introduced in Qt 5.11.
  QString text = "How many pixels wide is this text?";
  qInfo() << "Text width in pixels:" << metrics.width(text);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 11, 0))
  qInfo() << "Text width in pixels (horizontalAdvance):"
          << metrics.horizontalAdvance(text);
#endif

  qInfo() << "Text height in pixels:" << metrics.height();
}

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  TestFontCreation();
  qInfo() << "\n";

  TestFontDatabase();
  qInfo() << "\n";

  TestFontMetrics();

  return app.exec();
}
