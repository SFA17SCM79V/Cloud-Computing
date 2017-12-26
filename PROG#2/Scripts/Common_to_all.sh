// Mount EBS Volume using following
lsblk
sudo file -s /dev/xvdb
sudo mkfs -t ext4 /dev/xvdb
sudo mkdir /mnt/raid
sudo mount /dev/xvdb /mnt/raid
sudo chmod 777 /mnt/raid/

// Install java using following.
sudo apt-get update
sudo apt-add-repository ppa:webupd8team/java -y
sudo apt-get update
sudo apt-get install oracle-java8-installer -y

// Ant installation
sudo apt-get install ant
sudo apt-get update

// GCC installation
sudo apt-get install gcc -y
sudo apt-get update -y

// Open bashrc file and add the below details to the file. 
vi .bashrc 

export CONF=/home/ubuntu/hadoop-2.7.2/etc/hadoop
export JAVA_HOME=/usr/lib/jvm/java-8-oracle
export PATH=$PATH:$/home/ubuntu/hadoop-2.7.2/bin


Create folder to keep files in aws as /mnt/raid/TeraSort
Download gensort in your system and send file to /mnt/raid/TeraSort folder in aws using scp
chmod 777 gensort
Extract gensort and go the folder /gensort/64
generate the data accordingly.For example for 1GB use command ./gensort -a 10000000 a1.txt
Here the number indicates the number of records(each record 100 bytes) to be genrated not the file size and -a represents ascii data



