//Creating a RAID Array on Linux//

//(RAID 0 only) To create a RAID 0 array, execute the following command (note the --level=0 option to stripe the array):
sudo mdadm --create --verbose /dev/md0 --level=0 --name=hadoopterasort --raid-devices=2 /dev/xvdb /dev/xvdc

//Allow time for the RAID array to initialize and synchronize
sudo cat /proc/mdstat

//Create a file system on your RAID array, and give that file system a label to use when you mount it later 
sudo mkfs.ext4 -L hadoopterasort /dev/md0

//Create a mount point for your RAID array.
sudo mkdir -p /mnt/raid

// Finally, mount the RAID device on the mount point that you created:
udo mount LABEL=hadoopterasort /mnt/raid

// Create a backup of your /etc/fstab
sudo cp /etc/fstab /etc/fstab.orig

// To mount this Amazon EBS volume on every system reboot, add an entry for the device to the /etc/fstab file.
sudo vi /etc/fstab
LABEL=hadoopterasort    /mnt/raid   ext4    defaults,nofail        0       2

