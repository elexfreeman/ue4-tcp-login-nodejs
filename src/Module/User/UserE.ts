import { BaseResponseI } from "../Sys/ResponseSys";

export interface UserI {
    id?: number;
    login?: string;
    pswd?: string;
    user_name?: string;
}

export class UserE {
    public static NAME = 'users';
    ///....
}
export class UserTokenE {
    public static NAME = 'user_token';
    ///....
}


