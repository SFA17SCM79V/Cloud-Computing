Note:You can also follow the link in Reference.txt to setup single node and multi node cluster as they contains all the details.


sudo apt-get install ssh
sudo apt-get install rsync

wget http://www-us.apache.org/dist/hadoop/common/hadoop-2.7.4/hadoop-2.7.4.tar.gz

To setup single node of Hadoop we have done following configuration changes written below in /etc/hadoop/ file:

core-site.xml
<property>
  <name>fs.default.name</name>
  <value>hdfs://ec2-13-59-246-215.us-east-2.compute.amazonaws.com:54310</value>
  <description>The name of the default file system.  A URI whose
  scheme and authority determine the FileSystem implementation.  The
  uri's scheme determines the config property (fs.SCHEME.impl) naming
  the FileSystem implementation class.  The uri's authority is used to
  determine the host, port, etc. for a filesystem.</description>
</property>

hdfs-site.xml

<property>
  <name>dfs.replication</name>
  <value>1</value>
  <description>Default block replication.
  The actual number of replications can be specified when the file is created.
  The default is used if replication is not specified in create time.
  </description>
</property>

<property>
  <name>dfs.namenode.name.dir</name>
  <value>/mnt/raid/tmp/namenode</value>
</property>

<property>
  <name>dfs.blocksize</name>
  <value>268435456</value>
</property>

<property>
  <name>dfs.namenode.handler.count</name>
  <value>100</value>
</property>

<property>
  <name>dfs.datanode.data.dir</name>
  <value>/mnt/raid/tmp/datanode</value>
</property>

yarn-site.xml

<property>
<name>yarn.nodemanager.aux-services</name>
<value>mapreduce_shuffle</value>
</property>
<property>
<name>yarn.nodemanager.aux-services.mapreduce.shuffle.class</name>
<value>org.apache.hadoop.mapred.ShuffleHandler</value></property>
<property>
<name>yarn.resourcemanager.resource-tracker.address</name>
<value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:9025</value>
</property>
<property>
<name>yarn.resourcemanager.scheduler.address</name>
<value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:9030</value>
</property>
<property>
<name>yarn.resourcemanager.address</name>
<value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:9050</value>
</property>
<property>
<name>yarn.resourcemanager.webapp.address</name>
<value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:9006</value>
</property>
<property>
<name>yarn.resourcemanager.admin.address</name>
<value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:9008</value>
</property><!---->
<property>
<name>yarn.nodemanager.vmem-pmem-ratio</name>
<value>2.1</value>
</property>


/conf/slave 
Change this file default local host to aws instance name. After doing the above configuration changes we need to format hdfs

mapred-site.xml

<property>
  <name>mapred.job.tracker</name>
  <value>ec2-13-59-246-215.us-east-2.compute.amazonaws.com:54311</value>
  <description>The host and port that the MapReduce job tracker runs
  at.  If "local", then jobs are run in-process as a single map
  and reduce task.
  </description>
</property>

vi .bashrc 

export CONF=/home/ubuntu/hadoop-2.7.4/etc/hadoop
export JAVA_HOME=/usr/lib/jvm/java-8-oracle
export PATH=$PATH:$/home/ubuntu/hadoop-2.7.4/bin

Running Hadoop
 
./bin/hdfs namenode –format 
then we need to start all services ./sbin/start-all.sh through the start all scripts.

*Create directory in HDFS*
./bin/hadoop dfs –mkdir /mnt/raid/TeraSort/HDFSIn

*Copy the file generated by (Gensort) from local directory to a directory in HDFS*
./bin/hadoop dfs -copyFromLocal /mnt/raid/TeraSort/Input/actualInput.txt  /mnt/raid/TeraSort/HDFSIn/output

Compilation and run
Copy the hadoop code from your system to  /mnt/raid/TeraSort in aws
/usr/local/Hadoop/Hadoop2.7.4/bin/hadoop com.sun.tools.javac.Main TeraSort.java
jar cf TeraSort.jar TeraSort*.class
/usr/local/Hadoop/Hadoop2.7.4/bin/hadoop jar TerSort.jar TeraSort /mnt/raid/TeraSort/In /mnt/raid/output

For single node i3large cluster, we have run an experiment for approx 128 GB dataset, and for single node i34xlarge cluster, we have run an experiment for approx 1 TB dataset.

For an 8 node i3large cluster, we have run an assignment for approx 1 TB dataset.

To setup 8 node cluster
To set multiple nodes for hadoop we need to do keep the above configuration with few extra changes on below
mapred-site.xml
<property>
<name>mapreduce.cluster.local.dir</name>
<value>/mnt/raid/TeraSort</value>
</property>
<property>
<name>mapreduce.jobtracker.system.dir</name>			
<value>/mnt/raid/TeraSort</value>
</property>
<property>
<name>mapreduce.jobtracker.staging.root.dir</name>		
<value>/mnt/raid/TeraSort</value>
</property>
<property>
<name>mapreduce.cluster.temp.dir</name>		
<value>/mnt/raid/TeraSort</value>
</property>
<property>
<name>mapred.child.java.opts</name>
<value>-Xmx2048m-XX:+UseParallelOldGC</value>
</property>

hadoop-env.sh
export	HADOOP_CLIENT_OPTS="-Xmx2048m $HADOOP_CLIENT_OPTS"
export	HADOOP_PORTMAP_OPTS="-Xmx2048m -XX:+UseParallelOldGC	
$HADOOP_PORTMAP_OPTS"

follow the compilation and run steps for single node cluster after making changes
