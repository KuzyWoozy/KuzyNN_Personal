extern const int gradient_clip;

KuzyNN::teacher::Teacher::Teacher(const float& stepValue) : stepValue {stepValue} {}

KuzyNN::teacher::SGD::SGD(const float& stepValue, const KuzyMatrix::Matrix<double>& mat2teach) : Teacher(stepValue), param {&mat2teach}, buffer (mat2teach.get_shape()) {}

KuzyNN::teacher::SGD::SGD(const float& stepValue) : Teacher (stepValue) {}

void KuzyNN::teacher::SGD::update(const KuzyMatrix::Matrix<double>& paramWerror_vector) const {
    buffer.fill(stepValue);
    buffer.multiply(paramWerror_vector);
    buffer.clip((static_cast<double>(gradient_clip)));
    param->subtract(buffer);
}

KuzyNN::teacher::SGD& KuzyNN::teacher::SGD::bind(const KuzyMatrix::Matrix<double>& mat2teach) const {
    return *(new KuzyNN::teacher::SGD (stepValue, mat2teach));
}


KuzyNN::teacher::Momentum::Momentum(const float& stepValue, const float& momentum_friction) : Teacher {stepValue}, momentum_friction{momentum_friction} {}

KuzyNN::teacher::Momentum::Momentum(const float& stepValue, const float& momentum_friction, const KuzyMatrix::Matrix<double>& param) : Teacher {stepValue}, momentum_friction {momentum_friction}, param {&param}, buffer_step {param.get_shape()}, buffer_momentum {param.get_shape()}, buffer_prev {param.get_shape()} {
    buffer_step.fill(stepValue);
    buffer_momentum.fill(momentum_friction);
}


void KuzyNN::teacher::Momentum::update(const KuzyMatrix::Matrix<double>& paramWerror) const {
    buffer_prev = buffer_step * ((buffer_momentum * buffer_prev) + paramWerror);
    buffer_prev.clip(static_cast<double>(gradient_clip));
    param->subtract(buffer_prev);
}


KuzyNN::teacher::Momentum& KuzyNN::teacher::Momentum::bind(const KuzyMatrix::Matrix<double>& mat2teach) const {
    return *(new KuzyNN::teacher::Momentum (stepValue, momentum_friction, mat2teach));
}

