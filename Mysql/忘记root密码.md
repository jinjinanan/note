1. 苹果->系统偏好设置->最下边点mysql 在弹出页面中 关闭mysql服务

2. 终端输入: sudo /usr/local/mysql/bin/mysqld_safe --skip-grant-tables

3. 打开新的终端输入: 
	cd /usr/local/mysql/bin/
	./mysql
	FLUSH PRIVILEGES; 
	SET PASSWORD FOR 'root'@'localhost' = PASSWORD('你的新密码');