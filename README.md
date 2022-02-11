# bbb-bme280
BeagleBone Black based controller for the Bosch BME280.

Also spawns an HTTP server that serves plots of sensor data.

-------------------------------------------------------

### Dependencies

```
mkdir libmicrohttpd
cd libmicrohttpd
curl https://mirrors.ocf.berkeley.edu/gnu/libmicrohttpd/libmicrohttpd-latest.tar.gz -o libmicrohttpd-latest.tar.gz
tar --strip-components=1 -xz -f libmicrohttpd-latest.tar.gz
./configure
make
sudo make install
```
