#include <jni.h>
#include <string>
#include <android/log.h>
#include "include/openssl/evp.h"
#include "include/openssl/conf.h"
#include "include/openssl/err.h"

#define  TAG "Loopher"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,##__VA_ARGS__)

std::string encrypt(const std::string &plaintext, const std::string &key) {


    EVP_CIPHER_CTX *ctx;
    unsigned char iv[16] = {0}; // 初始化向量
    unsigned char ciphertext[1024];
    int len;
    int ciphertext_len;

    // 创建并初始化加密上下文
    if (!(ctx = EVP_CIPHER_CTX_new())) {
//        std::cerr << "Error in EVP_CIPHER_CTX_new" << std::endl;
        LOGD("%s", "Error in EVP_CIPHER_CTX_new");
        return "";
    }

    // 初始化加密操作
    if (1 !=
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *) key.c_str(), iv)) {
//        std::cerr << "Error in EVP_EncryptInit_ex" << std::endl;
        return "";
    }

    // 执行加密操作
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char *) plaintext.c_str(),
                               plaintext.length())) {
//        std:: << "Error in EVP_EncryptUpdate" << std::endl;
        return "";
    }
    ciphertext_len = len;

    // 结束加密操作
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
//        std::cerr << "Error in EVP_EncryptFinal_ex" << std::endl;
        return "";
    }
    ciphertext_len += len;

    // 释放加密上下文
    EVP_CIPHER_CTX_free(ctx);

    return std::string(reinterpret_cast<char *>(ciphertext), ciphertext_len);
}

// 解密函数
std::string decrypt(const std::string &ciphertext, const std::string &key) {
    EVP_CIPHER_CTX *ctx;
    unsigned char iv[16] = {0}; // 初始化向量
    unsigned char plaintext[1024];
    int len;
    int plaintext_len;

    // 创建并初始化解密上下文
    if (!(ctx = EVP_CIPHER_CTX_new())) {
//        std::cerr << "Error in EVP_CIPHER_CTX_new" << std::endl;
        return "";
    }

    // 初始化解密操作
    if (1 !=
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *) key.c_str(), iv)) {
        LOGD("%s", "Error in EVP_DecryptInit_ex");
        return "";
    }

    // 执行解密操作
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, (const unsigned char *) ciphertext.c_str(),
                               ciphertext.length())) {
        LOGD("%s", "Error in EVP_DecryptUpdate");
        return "";
    }
    plaintext_len = len;

    // 结束解密操作
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        LOGD("%s", "Error in EVP_DecryptFinal_ex");
        return "";
    }
    plaintext_len += len;

    // 释放解密上下文
    EVP_CIPHER_CTX_free(ctx);

    return std::string(reinterpret_cast<char *>(plaintext), plaintext_len);
}


extern "C"
JNIEXPORT void JNICALL
Java_me_bitefoo_androidencryptor_StringEncoder_postDeviceInfo(JNIEnv *env, jclass clazz,
                                                              jstring device_info) {
    // TODO: implement postDeviceInfo()

    // 要加密的明文和密钥
    std::string plaintext = "Hello, AES!";
    std::string key = "0123456789abcdef0123456789abcdef"; // 256位密钥


    LOGD("plaintext = %s", plaintext.c_str());
    // 加密
    std::string encrypted = encrypt(plaintext, key);
    LOGD("Encrypted text: %s", encrypted.c_str());
    // 解密
    std::string decrypted = decrypt(encrypted, key);
    LOGD("Decrypted text: %s", decrypted.c_str());


}