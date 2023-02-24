import React from 'react';
import { Link } from 'react-router-dom';
import LoginContainer from './LoginContainer';

const LoginPage = ({serverPort}) => {
  return <>
  <LoginContainer serverPort={serverPort}/>

  </>;
};

export default LoginPage;
