# You can also follow the detail configuration in link provided in Reference.txt

# Running Experiment on Single and Multiple nodes

# Need to export AWSAccessKeyId and AWSSecretKey then we need to run the below 

~/home/sandeep/Desktop/CS553/spark-1.6.3-bin-hadoop-2.7.4/ec2/spark-ec2 --keypair=Ec2s --identity-file=/home/sandeep/Desktop/EC2/PA2sandeepabhinav.pem –region=us-east-2 –zone=us-east-2a –instance-type=c3.large –slaves=7 –ebs-vol-size=1024 –spot-price=0.03 launch spark

# We need to do additional configuration as running sort for 128 GB and 1 TB as EBS volumes are ephemeral and hence we need to make these disks permanent.
# Changes that must be done to ensure persistent hdfs:

./ephemeral-hdfs/bin/stop-all.sh
sed -I s#vol/persistent-hdfs#vol0/persistent-hdfs#g’~/persistent-hdfs/conf/core-site.xml
~/spark-ec2/copy-dir.sh~/persistent-hdfs/conf/core-site.xml
~/persistent-hdfs/bin/hadoop namenode -format
~/persistent-hdfs/bin/start-all.sh
./persistent-hdfs/bin/hadoop dfs -mkdir /inputdir

# Now change spark configuration to use persistent-hdfs instead of ephemeralhdfs and set default directory from /mnt to /vol0.

# Go to spark config: /spark/conf/core-site.xml

# Change the hdfs url port from 9000 to 9010
# Change spark-env.sh
# spark default directory from /mnt to /vol0
# Restart Spark "Go to sbin and stop-all.sh then start-all.sh
# For spark experiment I have created 7 slaves and 1 master node with data set of 128 GB and 1024 GB.
