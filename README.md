# BilibiliAudioDownloader-cpp
参考[bilibiliAudioDownloader](https://github.com/nuster1128/bilibiliAudioDownloader)

## 主要功能
输入视频BV号列表，批量下载B站视频中的音频到本地, 音质固定为最大192kbps
## 使用说明

- Bv格式:
如果是普通视频,直接输入Bv号
如果是多p视频,输入***Bv号@起始集数-结束集数***(不指定@及后面参数,默认下载全部分p),例如:
- **下载普通视频: BV1Cv4y1m7Ub**
- **下载全部多p视频: BV1k94y1X7Nz**
- **下载多p视频中第7集: BV1k94y1X7Nz@7**
- **下载多p视频中的第1集至第3集: BV1k94y1X7Nz@1-3**
- **下载多p视频中的第77集至最后一集: BV1k94y1X7Nz@77-**

---

### 方式1 通过命令行下载(可批量)
- 在存放BilibiliAudioDownloader.exe的目录打开cmd,输入:
``` cmd
BilibiliAudioDownloader.exe -c Bv1 Bv2 ...
```

- 其中Bv1 Bv2 ... 为需要下载的Bv号,比如下载普通视频BV1UB4y1J7dS与多p视频BV1k94y1X7Nz的1至3集:
``` cmd
BilibiliAudioDownloader.exe -c BV1UB4y1J7dS BV1k94y1X7Nz@1-3
```

- 最终音频文件将下载到download文件夹中

### 方式2 读取文本文件下载(可批量)

- 新建一个txt文件存放要下载的bv号，如bvlist.txt。每行输入一个bv号，如
``` txt
BV1UB4y1J7dS
BV1k94y1X7Nz@1-3
BV1k94y1X7Nz@7
BV1k94y1X7Nz@40-48
BV1Cv4y1m7Ub
```
- 在存放BilibiliAudioDownloader.exe的目录打开cmd,输入:
``` cmd
BilibiliAudioDownloader.exe -f fileName
```
- 其中fileName为刚刚创建的文件名,如bvlist.txt,则为:
``` cmd
BilibiliAudioDownloader.exe -f bvlist.txt
```

- 最终音频文件将下载到download文件夹中

---

# 已知问题: 当下载音频名称中含有emoji时无法写入音频文件,在修了(咕咕咕...)
