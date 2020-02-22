# ros_redirect

Проект позволяет объединять два топика на разных компьютерах в один (перенаправлять сообщения с указанного топика через интернет в другой топик на другом компьютере).

### Зависимости
Для сборки проекта необходимо подключить следующие библиотеки (все эти библиотеки требуются для сборки ROS):
roscpp, rosconsole_log4cxx, rosconsole_backend_interface, log4cxx, console_bridge, rosconsole, roscpp_serialization, xmlrpcpp, rostime, cpp_common

### Использованные репозитории
Спасибо Markovvn1 (о, это я :blush:) за репозиторий [CrossSocket](https://github.com/Markovvn1/CrossSocket)   
Спасибо [Dennis](instructable.com/member/nqtronix) за файл compile_time.hpp

### Особенности
- Тип с которым будет работать программа, а так же как именно будет перводится этот тип в байты и наоборт нужно прописывать в файл ros.cpp (то есть он не может быть изменен после компиляции)
- В этом репозитории проект настроен для пересылки сообщения sensor_msgs/JointState
-  Для передачи информации нужно открыть порт (один порт для одного топика)
- Для передачи нескольких топиков достаточно запустить программу несколько раз с разными параметрами
- При запуске сервера указывается будет ли он публиковать или слушать сообщения по указанному топику. При подключении клиента ему автоматически передается эта информация

### Примеры
`./ros_redirect --help` - получить справку с описанием параметров
`./ros_redirect --server 1111 --subscribe /example/of/topic` - запустить сервер на 1111 порту, который будет подписан на топик /example/of/topic и пересылать с него сообщения клиенту
`./ros_redirect --server 1111 --publish /example/of/topic` - запустить сервер на 1111 порту, который будет публиковать сообщения, отправляемые клиентом, в топик /example/of/topic
`./ros_redirect --client 10.47.84.92:1111` - запустить клиент и подключиться к адресу  10.47.84.92 используя порт 1111. Клиент настраивается автоматически исходя из настроек сервера