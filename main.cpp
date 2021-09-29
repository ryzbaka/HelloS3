#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/logging/LogLevel.h>
#include <aws/s3/S3Client.h>

int main(){
	Aws::SDKOptions options;//default aws SDK config options.
	//config options are passed into Aws::InitAPI and Aws::ShutdownApi.
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;
	// the AWS SDK is initialized by calling the Aws::InitApi;
	Aws::InitAPI(options);
	{
		Aws::S3::S3Client client;
		auto outcome = client.ListBuckets();//synchronous fetch buckets.
		if(outcome.IsSuccess()){
			int numBuckets = outcome.GetResult().GetBuckets().size();
			std::cout<<"Found: "<<numBuckets<<" buckets.\n";
			if(numBuckets>0){
				for(auto &bucket:outcome.GetResult().GetBuckets()){
					std::cout<<bucket.GetName()<<"\n";
				}
			}	
		}else{
			std::cout<<"Failed with error:\n"<<outcome.GetError()<<"\n";
		}
	}
	Aws::ShutdownAPI(options);//Shutdown API before application termination.
	return 0;
}
