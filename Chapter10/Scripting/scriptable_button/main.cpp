#include <QApplication>
#include <QJSEngine>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QJSEngine engine;
    engine.installExtensions(QJSEngine::ConsoleExtension);
    QPushButton button;
    engine.globalObject().setProperty("pushButton", engine.newQObject(&button));
    QString script =
        "pushButton.text = 'My Scripted Button';\n"
        "pushButton.checkable = true;\n"
        "pushButton.setChecked(true);\n"
        "pushButton.toggled.connect(function() {\n"
        "  console.log('button toggled!');\n"
        "});\n"
        "pushButton.show();";
    engine.evaluate(script);

    QJSValue func = engine.evaluate(
          "function(checked) { console.log('func', checked); }");
    QObject::connect(&button, &QPushButton::clicked, [func](bool checked) {
        QJSValue(func).call({ checked });
    });
    return app.exec();
    return 0;
}
