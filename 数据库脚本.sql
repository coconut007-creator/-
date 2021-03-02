use Booksale;
create table users(
	u_id varchar(10),
	pwd varchar(64) not null,
	name varchar(10),
	w_id varchar(10),
	gender varchar(2),
	age varchar(2),
	degree varchar(1) not null,//1:super 2:ordinary
	primary key(u_id)
);
create table books(
	b_id varchar(10),
	ISBN varchar(10),
	b_name varchar(20),
	author varchar(20),
	publisher varchar(20),
	s_price numeric(5, 2),
	s_amount numeric(4,0),
	primary key(b_id)
	);
create table sell(
	b_id varchar(10),
	g_price numeric(5, 2),
	g_amount numeric(4,0),
	s_t varchar(2),
                primary key(b_id),
	foreign key (b_id) references books
)
create table account(
	a_date Date,
	budget numeric(10, 3),
	u_id varchar(10),
	a_type varchar(1)
	foreign key (u_id) references users
)
create table customer(
	c_id varchar(10),
	c_name varchar(20),
	c_degree varchar(1) not null,
	primary key(c_id)
	);



delete from users;
delete from books;
delete from sell;
delete from account;
delete from customer;
insert into books values ('1000000001', '1000000001', '李白全集','LI Bai','FDU','2.00','20');
insert into books values ('1000000002', '1000000002', '水调歌头','Shi Su','FDU','15.00','200');
insert into books values ('1000000003', '1000000003', '长恨歌','JuYi Bai','BKU','20.00','51');
insert into books values ('1000000004', '1000000004', '登高','Fu Du','FDU','12.00','49');
insert into books values ('1000000005', '1000000005', '望岳','NULL','FDU','22.00','100');
insert into books values ('1000000006', '1000000006', 'ICS','NULL','FDU','NULL','150');
insert into books values ('1000000007', '1000000007', '数据库系统概念','NULL','FDU','44.00','80');
insert into books values ('1000000008', '1000000008', '数据结构','RenKun Yin','THU','89.00','120');
insert into users values ('Tina', '0x81DC9BDB52D04DC20036DBD8313ED055', 'Tina Liu', '100001','f','30','1');
insert into users values ('Jennie', '0x827CCB0EEA8A706C4C34A16891F84E7B', 'Jennie Yu', '100002','f','25','2');
insert into users values ('John', '0x202cb962ac59075b964b07152d234b70', 'John Wu', '100003','m','31','1');
insert into users values ('Miller', '0x9996535e07258a7bbfd8b132435c5962', 'Miller Song', '100004','f','27','2');
insert into users values ('Mary', '0xe3251075554389fe91d17a794861d47b', 'Mary Huang', '100005','f','29','1');
insert into sell values ('1000000001', '9.90', '20', '3');
insert into sell values ('1000000002', '12.00', '20', '2');
insert into sell values ('1000000005', '4.50', '33', '2');
insert into sell values ('1000000006', '90.00', '400', '2');
insert into sell values ('1000000007', '99.00', '250', '2');
insert into account values ('2020-05-09', '240.000', 'Tina', '2');
insert into account values ('2020-05-10', '148.500', 'Jennie', '2');
insert into account values ('2020-05-08', '36000.000', 'John', '2');
insert into account values ('2020-05-01', '24750.000', 'Mary', '2');
insert into customer values ('100001', 'Lisa Wang', '2');
insert into customer values ('100002', 'Jennifer Shangguan', '3');
insert into customer values ('100003', 'Brown Guan', '2');
insert into customer values ('100001', 'Jones Li', '1');
