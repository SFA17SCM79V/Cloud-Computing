//Reference:https://hadoop.apache.org/docs/stable/hadoop-mapreduce-client/hadoop-mapreduce-client-core/MapReduceTutorial.html
//https://stackoverflow.com/questions/1770010/how-do-i-measure-time-elapsed-in-java
import java.io.IOException;
import java.util.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Job; 

public class TeraSort {

	public static class sortMap extends Mapper<Object, Text, Text, Text>  {
		
		public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
			
			String line = value.toString();
			String key1 = line.substring(0,10);
			String val1 = line.substring(10);
			Text key_convert = new Text();
                        Text value_convert = new Text();
			key_convert.set(key1);
                        value_convert.set(val1);
			context.write(key_convert,value_convert);
			
		}
	}

	public static class sortReduce extends  Reducer<Text, Text, Text, Text>  {
		public void reduce(Text key,Text values , Context context1) throws IOException, InterruptedException  {
			
	
			context1.write(key,values);
					
		}
	}

	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		//conf.set("dfs.block.size","512*1000*1000");
		Job tsort = new Job(conf,"Tera Sort");
		tsort.setJarByClass(TeraSort.class);
		
		tsort.setMapperClass(sortMap.class);
		tsort.setReducerClass(sortReduce.class);

		tsort.setOutputKeyClass(Text.class);
		tsort.setOutputValueClass(Text.class);

		FileInputFormat.addInputPath(tsort, new Path(args[0]));
		FileOutputFormat.setOutputPath(tsort, new Path(args[1]));

		long sTime=0;
		long eTime=0;
		sTime = System.currentTimeMillis();
		if(tsort.waitForCompletion(true)){
		eTime= System.currentTimeMillis();
		System.out.println("Total Time taken for Execution :" + (eTime-sTime)/1000);
		System.exit(0);
		}
		else{
		eTime = System.currentTimeMillis();
		System.out.println("Total time taken for execution:"+ (eTime-sTime)/1000);
		}
	}
}
