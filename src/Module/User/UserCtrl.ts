import { Components  } from '@a-a-game-studio/aa-classes/lib';
import { FieldValidator } from '@a-a-game-studio/aa-components/lib';
import { UserSQL } from './UserSQL';
import { UserI } from './UserE';
import { faUserLoginV } from './UserV';
import { aSocketClient } from '../Sys/db';
import { UserLogin } from './UserR';
import * as net from "net";
import { fBaseRequest, fResponse } from '../Sys/ResponseSys';




/**
 * Контролер пользователя
 */
export const faUserLogin = async (socket: net.Socket, request: fBaseRequest, errorSys: Components.ErrorSys, db: any) => {

   const userSQL = new UserSQL(errorSys, db);
   let cValidator = new FieldValidator(errorSys, {});
   let sToken = '';
   let user: UserI;

   try {

      const data: UserLogin.RequestI = request.data;

      /* валидируем входные данные */
      cValidator = faUserLoginV(data, cValidator);

      if (!cValidator.fIsOk()) {
         throw 'error';
      }

      /* получаем ответ от DB */
      sToken = await userSQL.faGetTokenByLoginAndPass(data.login, data.pswd);

      /* проверяем есть ли токен */
      cValidator.fSetErrorString('token')
         .fSetData(sToken)
         .fExist()
         .fMinLen(32)
         .fMaxLen(32);

      if (cValidator.fIsOk()) {
         user = await userSQL.faGetUserInfoByToken(sToken);
      }


   } catch (e) {
      /* все плохо с базой */
      cValidator.fSetErrorString('all bad')
         .fSetData(null)
         .fExist(e);
   }

   /* формируем ответ */
   const resp: UserLogin.ResponseI = {
      sRoute: UserLogin.sResponseRoute,
      ok: cValidator.fIsOk(),
      data: {
         token: sToken,
         user: user,
      },
      errors: cValidator.fGetErrorSys().getErrors()
   }

   /* отправляем клиенту сообщение */
   fResponse(socket, resp);

   /* если все хорошо записываем информацию о юзере в общую память  */
   if (cValidator.fIsOk()) {
      aSocketClient[request.sClientToken] = {
         token: sToken,
         user: user,
      }
   }

   console.log('faUserLogin msg', request.data);

}