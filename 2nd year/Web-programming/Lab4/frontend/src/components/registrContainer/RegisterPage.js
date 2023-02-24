import React from 'react';
import { Link } from 'react-router-dom';
import RegistrContainer from './RegistrContainer';

const RegisterPage = ({serverPort}) => {
  return <>
  <RegistrContainer serverPort={serverPort}/>

  </>;
};

export default RegisterPage;