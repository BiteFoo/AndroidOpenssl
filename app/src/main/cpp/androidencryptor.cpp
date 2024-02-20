#include <jni.h>
#include <string>
#include <android/log.h>
#include "include/openssl/evp.h"
#include "include/openssl/conf.h"
#include "include/openssl/err.h"
//给base64使用
#include "include/openssl/bio.h"
#include "include/openssl/buffer.h"
#include "md5.h"
#include "rc4.h"

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

// Base64 编码函数
std::string base64_encode(const std::string &input) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_write(bio, input.c_str(), input.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string result(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);
    return result;
}

// Base64 解码函数
std::string base64_decode(const std::string &input) {
    BIO *bio, *b64;
    char *buffer = new char[input.size()];
    memset(buffer, 0, input.size());
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf(input.c_str(), input.length());
    bio = BIO_push(b64, bio);
    BIO_read(bio, buffer, input.size());
    BIO_free_all(bio);
    std::string result(buffer);
    delete[] buffer;
    return result;
}
// MD5 哈希计算函数
std::string md5_hash(const std::string &input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((const unsigned char *)input.c_str(), input.length(), digest);
    char mdString[33];
    for (int i = 0; i < 16; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
    return std::string(mdString);
}

// RC4 加密函数
std::string rc4_encrypt(const std::string &plaintext, const std::string &key) {
    RC4_KEY rc4_key;
    RC4_set_key(&rc4_key, key.length(), (const unsigned char *)key.c_str());
    unsigned char *plaintext_buffer = (unsigned char *)plaintext.c_str();
    unsigned char *ciphertext_buffer = new unsigned char[plaintext.length()];
    RC4(&rc4_key, plaintext.length(), plaintext_buffer, ciphertext_buffer);
    std::string ciphertext(reinterpret_cast<char *>(ciphertext_buffer), plaintext.length());
    delete[] ciphertext_buffer;
    return ciphertext;
}

// RC4 解密函数
std::string rc4_decrypt(const std::string &ciphertext, const std::string &key) {
    return rc4_encrypt(ciphertext, key); // RC4 加密和解密使用相同的算法
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
    LOGD("======Aes=====");
    std::string encrypted = encrypt(plaintext, key);
    LOGD("Encrypted text: %s", encrypted.c_str());
    // 解密
    std::string decrypted = decrypt(encrypted, key);
    LOGD("Decrypted text: %s", decrypted.c_str());
    //
    LOGD("Base64----testing");
    std::string base64EncodeText = base64_encode(plaintext);
    LOGD("Base64Encode: %s",base64EncodeText.c_str());
    std::string base64DecodeText = base64_decode(base64EncodeText);
    LOGD("Base64Decode: %s",base64DecodeText.c_str());
    LOGD("Md5计算原始字符串内容: %s", md5_hash(plaintext).c_str());
    LOGD("RC4=====");
    std::string rc4_encode = rc4_encrypt(plaintext,key);
    LOGD("RC4 encode: %s",rc4_encode.c_str());
    std::string rc4_decode = rc4_decrypt(rc4_encode,key);
    LOGD("RC4 decode: %s",rc4_decode.c_str());



}