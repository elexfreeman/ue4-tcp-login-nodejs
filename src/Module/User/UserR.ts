import { BaseResponseI } from "../Sys/ResponseSys";
import { UserI } from "./UserE";

/**
 * Вход пользователя
 */
export namespace UserLogin {

   export const sRequestRoute = 'user_login_req';
 
   export const sResponseRoute = 'user_login_resp';

    export interface RequestI {
       login: string;
       pswd: string;
    }
   
 
    export interface ResponseI extends BaseResponseI {
       data: {
          token: string;
          user: UserI;
       }
    }
 }
 