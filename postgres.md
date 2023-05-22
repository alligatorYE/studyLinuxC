## postgres
```bash
ALTER USER postgres WITH PASSWORD 'postgres'

sudo -i -u postgres
sudo su postgres //切换SQL用户登录
psql -U postgres //空密码登录
alter user postgres with password 'postgres'; //修改postgres 用户密码
alter user postgres with password 'postgres';
```
## MySql

```bash
mysql>use mysql;
mysql>flush privileges;
mysql>ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'yangele@root';
mysql>flush privileges;
```


```bash
sudo groupadd mysql
sudo useradd -r -g mysql -s /bin/false mysql
sudo cd /usr/local
sudo tar xvf /path/to/mysql-VERSION-OS.tar.xz
sudo ln -s full-path-to-mysql-VERSION-OS mysql
sudo cd mysql
sudo mkdir mysql-files
sudo chown mysql:mysql mysql-files
sudo chmod 750 mysql-files
sudo bin/mysqld --initialize --user=mysql
sudo bin/mysql_ssl_rsa_setup
sudo bin/mysqld_safe --user=mysql &
# Next command is optional
sudo cp support-files/mysql.server /etc/init.d/mysql.server
```
2023-04-28T10:36:45.247464Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: /ppZC9J#p&:l

```bash
sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password by 'root';



