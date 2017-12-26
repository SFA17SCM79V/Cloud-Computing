val sTime = System.currentTimeMillis()

val in_file=sc.textFile("hdfs://ec2-13-59-246-215.us-east-2.compute.amazonaws.com:54310/mnt/raid/HDFSIn/actualIn.txt")

val sorting_f =in_file.map(line => (line.take(10), line.drop(10)))

val sorted_data = sorting_f.sortByKey()

val lines=sorted_data.map {case (key,value) => s"$key $value"}

lines.saveAsTextFile("/mnt/raid/SparkOutput")

val eTime = System.currentTimeMillis()

println ("Total time :" + ((eTime - sTime)))