import React from 'react';
import PropTypes from 'prop-types';

const Button = ({color, text, onClick}) => {
  return <button className='btn' onClick={onClick} style={{background : color}}>{text}</button>;
};

export default Button;

Button.defaultProps = {
  color : "#BB5B3F"
}

Button.propTypes = {
  text: PropTypes.string,
  color: PropTypes.string,
  onClick: PropTypes.func
}
