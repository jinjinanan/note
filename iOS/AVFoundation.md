# AVFoundation

## 应用

### 获得视频截图

``` Objective-C
/**
 *  截取指定时间的视频缩略图
 *
 *  @param timeBySecond 时间点
 */
-(void)thumbnailImageRequest:(CGFloat )timeBySecond{
    //创建URL
    NSURL *url=[self getNetworkUrl];
     
    //根据url创建AVURLAsset
    AVURLAsset *urlAsset=[AVURLAsset assetWithURL:url];
     
    //根据AVURLAsset创建AVAssetImageGenerator
    AVAssetImageGenerator *imageGenerator=[AVAssetImageGenerator assetImageGeneratorWithAsset:urlAsset];
     
    /*截图
     * requestTime:缩略图创建时间
     * actualTime:缩略图实际生成的时间
     */
      
    NSError *error=nil;
    CMTime time=CMTimeMakeWithSeconds(timeBySecond, 10);//CMTime是表示电影时间信息的结构体，第一个参数表示是视频第几秒，第二个参数表示每秒帧数.(如果要活的某一秒的第几帧可以使用CMTimeMake方法)
    CMTime actualTime;
     
    CGImageRef cgImage= [imageGenerator copyCGImageAtTime:time actualTime:&actualTime error:&error];
     
    if(error){
     
        NSLog(@"截取视频缩略图时发生错误，错误信息：%@",error.localizedDescription);
         
        return;
    }
     
    CMTimeShow(actualTime);
     
    UIImage *image=[UIImage imageWithCGImage:cgImage];//转化为UIImage
     
    //保存到相册
    UIImageWriteToSavedPhotosAlbum(image,nil, nil, nil);
     
    CGImageRelease(cgImage);
}
```

---
| 单词       | 词性   |  词义  |
| --------   | -----:  | :----:  |
|audiovisual||
|assest||
|architecture||
|reencode||
|manipulate||
|during realtime capture and playback||

[AVFoundation翻译](http://blog.csdn.net/zyq522376829/article/details/52144317)




