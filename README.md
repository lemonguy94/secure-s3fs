# secure-s3fs
CSC4420: Operating Systems - Final Course Project
Design and Implementation of A Secure Amazon S3 Based File System 

This project is the design and implementation of a stackable file system running on Linux and using Amazon S3 as backend storage.  The source code contains a slightly altered version of s3fs-1.80, using OpenSSL's RC4.  It accomplishes the following:

- When mounted, a bucket in S3 is created as a local directory on your Linux machine
- Any updates in the mounted directory are reflected in the S3 bucket and vice versa
- All files in the mounted directory are automatically encrypyted to the S3 bucket using an implementation of OpenSSL's RC4

## Setup for S3 bucket and mount

#### First, create an AWS account with Amazon Web Services and create your bucket by doing the following:

- Go to aws.amazon.com
- Create an AWS account or log in if you have an account
- Navigate to S3, under storage
- Create your bucket

Once you do this, an email should be sent to you which contains your identity and credential.  This will be used later when mounting your local directory. 

#### Second, make sure you have all of the dependencies

Enter the following onto the Ubuntu command line:

```
sudo apt-get install automake autotools-dev g++ git libcurl4-gnutls-dev libfuse-dev libssl-dev libxml2-dev make pkg-config
```

(I will insert more here about installation once I upload to github, I won't describe the installation process here for my project submission as I already have all of the source code submitted along with this.  This would be the third step, so I will move onto the fourth step now)

#### Fourth, mount your local directory

Enter your S3 identity and credential in a file `/path/to/passwd`:

```
echo MYIDENTITY:MYCREDENTIAL > /path/to/passwd
```

Give your file the proper permissions:

```
chmod 666 /path/to/passwd
```

Specify the path:

```
PATH=$PATH:/home/path/to/s3fs-fuse
```

Test to see if the path is specified:

```
which s3fs
```

Finally, mount your specified directory:

```
s3fs YourBucketName /path/to/mount -o passwd_file=/path/to/passwd -o umask=0000
```

With this, you should have created your local mount point, which connects to your S3 bucket.

## Configure

#### Encryption key: In order to use a key for RC4 encryption other than the default, you will want to create a .txt file which contains a single line, which is your RC4 crypt key.  

To do this:

- Create a text file containing your key, this can be located wherever you feel like
- Navigate to the directory /path/to/s3fs-fuse/src and open fdcache.cpp in a text editor
- Go to line 67, and change the path to the new path for the key that you created

Note: any time that you change the path for your encryption key, you must navigate to the s3fs-fuse directory and type "make" into the command line.  When you do this, you will also need to remount your local directory.  To unmount, type the following:

```
fusermount -u /path/to/mount
```

After this, repeat the steps above to remount.  

## Notes

- The RC4 implementation here does not work along with the OpenSSL's built-in crypt command.  
- (PROJECT): You may want to go to rc4project.cpp in the standalone implementation directory, where you will again change the path to your new RC4 key path.  Note that after doing this, you must recompile using g++ rcproject4.cpp. 
- You will need to remount the local directory on system boot.  I will implement a script that does this automatically sometime later.
