# Comando para compilar usando una imagen docker de ESP-idf_component_register
#
docker run --rm -v $PWD:/project -w /project espressif/idf:v4.4 idf.py build

#
# Comando para flashear
#
docker run --rm --device=/dev/ttyUSB0 -v $PWD:/project -w /project espressif/idf:v4.4 idf.py --port /dev/ttyUSB0 flash

#
# Para poder hacer uso mas comodamente de la libreria de drivers y componentes ya desarrollados ESP-IDF-LIB 
# conviene buildear una imagen Docker extendiendo la de Espressif e incluyendo estos.
#
# Para ello basta con crear una imagen del Dockerfile en el mismo dir y usarla para compilar los prototipos.
#
docker build --tag esp_custom_building .

#
# y luego buildear usando 
#
docker run --rm -v $PWD/<PROJECTO A BUILDEAR>:/project esp_custom_building idf.py build

docker run --rm -v $PWD/esp32-bmp280:/project esp_gonzalo_building idf.py build
docker run --rm -v $PWD/esp32-joystick:/project esp_gonzalo_building idf.py build
docker run --rm -v $PWD/esp32-dht11:/project esp_gonzalo_building idf.py build
docker run --rm -v $PWD/esp32-photoresistor:/project esp_gonzalo_building idf.py build
docker run --rm -v $PWD/esp32-integracion:/project esp_gonzalo_building idf.py build


#
# y flashear usando 
#
docker run --rm --device=/dev/ttyUSB0 -v $PWD/esp32-bmp280:/project esp_gonzalo_building idf.py flash --port /dev/ttyUSB0
docker run --rm --device=/dev/ttyUSB0 -v $PWD/esp32-joystick:/project esp_gonzalo_building idf.py flash --port /dev/ttyUSB0
