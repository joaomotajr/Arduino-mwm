@ECHO OFF
REM start.bat  code
java -jar -Dlog4j.configuration=file:///%CD%\cfg\log4j.properties xBeeMqttEneeyes-0.0.1-SNAPSHOT-jar-with-dependencies.jar %1 %2 %3