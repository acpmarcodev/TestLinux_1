#include <jni.h>
#include <android/log.h>
#include <bluetooth.h>
#include <rfcomm.h>

#define TAG "Bluetooth"

JNIEXPORT void JNICALL Java_com_example_Bluetooth_connect(JNIEnv *env, jobject obj, jstring device_address)
{
    // Obter endereço do dispositivo
    const char *address = env->GetStringUTFChars(device_address, NULL);

    // Inicializar socket Bluetooth
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = { 0 };

    // Copiar endereço do dispositivo para o formato apropriado
    snprintf(dest, sizeof(dest), "%s", address);
    //str2ba( dest, &addr.rc_bdaddr );

    // Definir parâmetros do socket Bluetooth
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;

    // Abrir socket Bluetooth
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // Conectar ao dispositivo
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if(status == 0){
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "Bluetooth connected");
    }else{
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "Bluetooth connection failed");
    }

    // Liberar memória
    //close(s);
    env->ReleaseStringUTFChars(device_address, address);
}