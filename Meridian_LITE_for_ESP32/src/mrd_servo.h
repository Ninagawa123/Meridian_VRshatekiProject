#ifndef __MERIDIAN_SERVO_DISTRIBUTOR_H__
#define __MERIDIAN_SERVO_DISTRIBUTOR_H__

// ヘッダファイルの読み込み
#include "config.h"
#include "main.h"
#include "mrd_module/sv_ftbrx.h"
#include "mrd_module/sv_ics.h"

//==================================================================================================
//  Servo 関連の処理
//==================================================================================================

//------------------------------------------------------------------------------------
//  各UARTの開始
//------------------------------------------------------------------------------------

/// @brief 指定されたUARTラインとサーボタイプに基づいてサーボの通信プロトコルを設定する.
/// @param a_line UART通信ライン(L, R, またはC).
/// @param a_servo_type サーボのタイプを示す整数値.
/// @return サーボがサポートされている場合はtrueを, サポートされていない場合はfalseを返す.
bool mrd_servo_begin(UartLine a_line, int a_servo_type)
{
  switch (a_servo_type)
  {
  case 1:
    // single PWM [WIP]
    return false;
  case 11:
    // I2C_PCA9685 to PWM [WIP]
    return false;
  case 21:
    // RSxTTL (FUTABA) [WIP]
    return false;
  case 31:
    // DYNAMIXEL Protocol 1.0 [WIP]
    return false;
  case 32:
    // DYNAMIXEL Protocol 2.0 [WIP]
    return false;
  case 43:
    if (a_line == L)
      ics_L.begin(); // サーボモータの通信初期設定. Serial2
    else if (a_line == R)
      ics_R.begin(); // サーボモータの通信初期設定. Serial3
    return true;
  case 44:
    // PMX(KONDO) [WIP]
    return false;
  case 51:
    // XBUS(JR PROPO) [WIP]
    return false;
  case 61:
    // STS(FEETECH) [WIP]
    return false;
  case 62:
    // SCS(FEETECH) [WIP]
    return false;
  default:
    // Not defined.
    return false;
  }
}

//------------------------------------------------------------------------------------
//  サーボ通信フォーメーションの分岐
//------------------------------------------------------------------------------------

/// @brief 指定されたサーボにコマンドを分配する.
/// @param a_meridim サーボの動作パラメータを含むMeridim配列.
/// @param a_L_type L系統のサーボタイプ.
/// @param a_R_type R系統のサーボタイプ.
/// @param a_sv サーボパラメータの構造体.
/// @return サーボの駆動が成功した場合はtrueを, 失敗した場合はfalseを返す.
bool mrd_servo_drive_lite(Meridim90Union &a_meridim, int a_L_type, int a_R_type, ServoParam &a_sv)
{
  if (a_L_type == 43 && a_R_type == 43) // ICSサーボがL系R系に設定されていた場合はLR均等送信を実行
  {
    mrd_sv_drive_ics_double(a_meridim, a_sv);
    return true;
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------------
//  各種オペレーション
//------------------------------------------------------------------------------------

/// @brief 第一引数のMeridim配列のすべてのサーボモーターをオフ(フリー状態)に設定する.
/// @param a_meridim サーボの動作パラメータを含むMeridim配列.
/// @return 設定完了時にtrueを返す.
bool mrd_servo_all_off(Meridim90Union &a_meridim)
{
  for (int i = 0; i < 15; i++)
  {                                 // 15はサーボ数
    a_meridim.sval[i * 2 + 20] = 0; // サーボのコマンドをオフに設定
    a_meridim.sval[i * 2 + 50] = 0; //
  }
  Serial.println("All servos torque off.");
  return true;
}

/// @brief サーボパラメータからエラーのあるサーボのインデックス番号を作る.
/// @param a_sv サーボパラメータの構造体.
/// @return uint8_tで番号を返す.
///         100-149(L系統 0-49),200-249(R系統 0-49)
uint8_t mrd_servo_make_errcode_lite(ServoParam a_sv)
{
  uint8_t servo_ix_tmp = 0;
  for (int i = 0; i < 15; i++)
  {
    if (a_sv.ixl_stat[i])
    {
      servo_ix_tmp = uint8_t(i + 100);
    }
    if (a_sv.ixr_stat[i])
    {
      servo_ix_tmp = uint8_t(i + 200);
    }
  }
  return servo_ix_tmp;
}

float mrd_servo_move_limit(float a_previous, float a_current, float a_limit)
{
  float diff = a_current - a_previous;

  if (fabs(diff) <= a_limit)
  {
    // 移動量が制限値以下の場合、そのまま目標値を返す
    return a_current;
  }
  else
  {
    // 移動量が制限値を超える場合、制限値分だけ移動
    if (diff > 0)
    {
      // 正方向への移動
      return a_previous + a_limit;
    }
    else
    {
      // 負方向への移動
      return a_previous - a_limit;
    }
  }
}

#endif // __MERIDIAN_SERVO_DISTRIBUTOR_H__
