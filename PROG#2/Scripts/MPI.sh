Running mpi on single node
The setup for single node is easy. We have written the steps below 
tar -xzf mpich2-1.4.tar.gz
cd mpich2-1.4
./configure --disable-fortran
make; sudo make install

Compile your 3 files:

gcc -o TeraSort mpi_Terasort.c 
mpii -o sort sort.c
mpii -o merge merge.c

Now Run you file
./Terasort input_file_name

Running mpi on 8 node cluster
sudo easy_install StarCluster
starcluster help
Since StarCluster is not configured, it will print out the following 
StarCluster - (http://web.mit.edu/starcluster) (v. 0.93.3)
Software Tools for Academics and Researchers (STAR)
Please submit bug reports to starcluster@mit.edu

!!! ERROR - config file /Users/wesleykendall/.starcluster/config does not exist

Options:
--------
[1] Show the StarCluster config template
[2] Write config template to /Users/wesleykendall/.starcluster/config
[q] Quit

Please enter your selection:
Enter the number 2 and StarCluster will generate a default configuration file in your home directory under ~/.starcluster/config.
Obtain your AWS access key, secret access key, and your 12-digit user ID from your AWS account.
open your default config file (~/.starcluster/config) with your favorite text editor. Find the line with [aws info] and enter all of your AWS information into the proper fields:
AWS_ACCESS_KEY_ID = # Your Access Key ID here
AWS_SECRET_ACCESS_KEY = # Your Secret Access Key here
AWS_USER_ID = # Your 12-digit AWS Account ID here (no hyphens)

save the config file and then create a public/private key pair that will be uploaded to Amazon and used to authenticate your machine when you log into your cluster

starcluster createkey mykey -o ~/.ssh/mykey.rsa
configuring cluster parameters
KEYNAME = mykey
CLUSTER_SIZE = 8
CLUSTER_USER = abhinav@ 
CLUSTER_SHELL = bash
NODE_IMAGE_ID = virtual machine image
NODE_INSTANCE_TYPE = i3.large

enable the mpich2 plugin for Starcluster.Compile your program in the same way as single node and run your program.
                                      

