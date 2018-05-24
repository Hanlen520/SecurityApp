package com.atomone.Secureinspect.listener;

/**
 * 签名效验时会调用，签名合法调用success，签名非法调用fail，用户可以在fail进行处理，
 * 比如退出程序，或者提示用户下载正版等等，具体业务逻辑业务方自己实现
 */
public interface IVerifyListener {
    /**
     * 签名校验失败
     */
    void onVerifySuccess();

    /**
     * 签名校验成功
     */
    void onVerifyFail();
}
