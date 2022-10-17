# OpenACC测试
* 环境 Ubuntu 20.04 + gcc 11.1 gpu:gtx-3070
* 需要安装及配置
    * apt install nvptx-tools gcc-11-offload-nvptx
    * export GOMP_DEBUG=1 ; export ACC_DEVICE_TYPE=nvidia
* 矩阵乘法测试结果

![](img/res.png)