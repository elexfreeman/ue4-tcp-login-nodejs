export interface ConfI {
    env: string; // prod - dev
    mysql: {
        client: string;
        connection: {
            host: string;
            user: string;
            password: string;
            database: string;
        };
        pool: {
            min: number;
            max: number;
        };
        migrations: {
            tableName: string;
            directory: string;
        };
        acquireConnectionTimeout: number;
    };
    redis?: {
        url: string;
    };  
    common: {
        port: number;
    };
}